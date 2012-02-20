/**
 * Read3DS.cpp
 *
 *  @date 10.12.2011
 *  @author Thomas Wiemann
 */

#include "Read3DS.hpp"

#include "SDL.h"
#include "C3DSMaterialReader.h"
#include "C3DSMeshReader.h"
#include "C3DSMeshNormalCalculator.h"

#include <iostream>
#include <map>
using std::cout;
using std::endl;
using std::map;

void Read3DS::getMesh(TexturedMesh& texMesh)
{
    SDL_RWops *rw = SDL_RWFromFile(m_filename.c_str(), "rb");

    // Parse materials
    map<string, int> matMap;

    C3DSMaterialReader matReader(rw);
    matReader.parse();

    for(size_t i = 0; i < matReader.materials().size(); i++)
    {
        C3DSMaterialReader::Material m = matReader.materials()[i];

        // Convert name into ID
        matMap[m.name] = (int)i;

        // Convert to Material struct
        Material* mat = new Material;
        mat->m_ambient.r = m.colorAmbient[0];
        mat->m_ambient.g = m.colorAmbient[1];
        mat->m_ambient.b = m.colorAmbient[2];

        mat->m_diffuse.r = m.colorDiffuse[0];
        mat->m_diffuse.g = m.colorDiffuse[1];
        mat->m_diffuse.b = m.colorDiffuse[2];

        mat->m_specular.r = m.colorSpecular[0];
        mat->m_specular.g = m.colorSpecular[1];
        mat->m_specular.b = m.colorSpecular[2];
        mat->m_shininess = m.shininess;

        // Load texture from file
        if(m.texMaps.size() > 0)
        {
            mat->m_texture = TextureFactory::instance().getTexture(m.texMaps[0].filename);
        }
        else
        {
            mat->m_texture = 0;
        }

        texMesh.addMaterial(mat);
    }

    // Reset file pointer
    SDL_RWseek(rw, 0, SEEK_SET);

    // Read geometry
    C3DSMeshReader      meshReader(rw);
    meshReader.parse();

    // Create a mesh with normals
    C3DSMeshNormalCalculator normalMesh(meshReader);
    normalMesh.calculate();

    // Save geometry information and merge with material info
    for(size_t i = 0; i < normalMesh.meshes().size(); i++)
    {

        C3DSMeshNormalCalculator::Mesh &mesh = normalMesh.meshes()[i];
        m_numVertices += mesh.vertices.size();
        m_numFaces += mesh.faces.size();
    }

    // Alloc memory for buffers
    m_vertexBuffer  = new float [3 * m_numVertices];
    m_normalBuffer  = new float [3 * m_numVertices];
    m_indexBuffer   = new int   [3 * m_numFaces];
    float* textureBuffer = new float[2 * m_numVertices];

    // Fill buffers
    size_t vertexCount  = 0;
    size_t startFace    = 0;

    for(size_t i = 0; i < normalMesh.meshes().size(); i++)
    {
        C3DSMeshNormalCalculator::Mesh &n_mesh = normalMesh.meshes()[i];
        C3DSMeshReader::Mesh &mesh = meshReader.meshes()[i];

        for(size_t j = 0; j < mesh.vertices.size(); j++)
        {
            size_t vBufferIndex = 3 * vertexCount;
            size_t cBufferIndex = 2 * vertexCount;

            for(int a = 0; a < 3; a++)
            {
                m_vertexBuffer[vBufferIndex + a] = mesh.vertices[j][a];
                m_normalBuffer[vBufferIndex + a] = n_mesh.normals[j][a];
            }

            if(j < mesh.mapCoords.size())
            {
                textureBuffer[cBufferIndex]      = mesh.mapCoords[j].u;
                textureBuffer[cBufferIndex + 1]  = mesh.mapCoords[j].v;
             }
            else
            {
                textureBuffer[cBufferIndex]  = 0.0f;
                textureBuffer[cBufferIndex + 1]  = 0.0f;
            }

            vertexCount++;
        }

        for(size_t j = 0; j < mesh.faceMaterials.size(); j++)
        {
            C3DSMeshReader::FaceMaterial fm = mesh.faceMaterials[j];
            MaterialFaceList* matList = new MaterialFaceList;
            matList->m_matIndex = matMap[fm.name];

            for(size_t a = 0; a < fm.faces.size(); a++)
            {
                C3DSMeshReader::Face cFace = mesh.faces[fm.faces[a]];
                matList->m_faces.push_back(cFace.indices[0] + startFace);
                matList->m_faces.push_back(cFace.indices[1] + startFace);
                matList->m_faces.push_back(cFace.indices[2] + startFace);
            }

            texMesh.addMaterialFaceList(matList);
        }
        startFace += mesh.vertices.size();

    }

    // Save buffer in mesh
    texMesh.setVertexBuffer(m_vertexBuffer, m_numVertices);
    texMesh.setIndexBuffer(m_indexBuffer, m_numFaces);
    texMesh.setNormalBuffer(m_normalBuffer);
    texMesh.setTextureBuffer(textureBuffer);

}

Read3DS::Read3DS(string filename)
{
    m_filename = filename;
}

void Read3DS::readSimpleMesh()
{
    SDL_RWops *rw = SDL_RWFromFile(m_filename.c_str(), "rb");

    //C3DSMaterialReader  matReader(rw);

    // Parse mesh
    C3DSMeshReader      meshReader(rw);
    meshReader.parse();

    // Create a mesh with normals
    C3DSMeshNormalCalculator normalMesh(meshReader);
    normalMesh.calculate();

    // Calc vertices and faces in all mesh groups
    for(size_t i = 0; i < normalMesh.meshes().size(); i++)
    {

        C3DSMeshNormalCalculator::Mesh &mesh = normalMesh.meshes()[i];

        m_numVertices += mesh.vertices.size();
        m_numFaces += mesh.faces.size();
    }

    // Alloc memory for buffers
    m_vertexBuffer  = new float [3 * m_numVertices];
    m_normalBuffer  = new float [3 * m_numVertices];
    m_indexBuffer   = new int   [3 * m_numFaces];

    // Fill buffers
    size_t vertexCount  = 0;
    size_t faceCount    = 0;

    size_t startFace    = 0;

    for(size_t i = 0; i < normalMesh.meshes().size(); i++)
    {
        C3DSMeshNormalCalculator::Mesh &mesh = normalMesh.meshes()[i];

        for(size_t j = 0; j < mesh.vertices.size(); j++)
        {
            size_t vBufferIndex = 3 * vertexCount;
            for(int a = 0; a < 3; a++)
            {
                m_vertexBuffer[vBufferIndex + a] = mesh.vertices[j][a];
                m_normalBuffer[vBufferIndex + a] = mesh.normals[j][a];
            }
            vertexCount++;
        }


        for(size_t j = 0; j < mesh.faces.size(); j++)
        {
            size_t fBufferIndex = 3 * faceCount;
            for(int a = 0; a < 3; a++)
            {
                m_indexBuffer[fBufferIndex + a] = mesh.faces[j].indices[a] + startFace;

            }
            faceCount++;
        }
        startFace += mesh.vertices.size();
    }

}

TriangleMesh* Read3DS::getMesh()
{
    readSimpleMesh();
    if(m_vertexBuffer && m_indexBuffer)
    {
        TriangleMesh* mesh = new TriangleMesh;
        mesh->setVertexBuffer(m_vertexBuffer, m_numVertices);
        mesh->setIndexBuffer(m_indexBuffer, m_numFaces);
        mesh->setNormalBuffer(m_normalBuffer);

        return mesh;
    }
    else
    {
        return 0;
    }
}


Read3DS::~Read3DS()
{
    // TODO Auto-generated destructor stub
}

