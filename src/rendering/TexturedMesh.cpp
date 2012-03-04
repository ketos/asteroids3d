/**
 * TexturedMesh.cpp
 *
 *  @date 13.12.2011
 *  @author Thomas Wiemann
 */

#include "TexturedMesh.hpp"

TexturedMesh::TexturedMesh()
{

}

TexturedMesh::TexturedMesh(const TexturedMesh &mesh)
{
}


TexturedMesh::~TexturedMesh()
{

}

void TexturedMesh::compileDisplayList()
{
//    m_displayList = glGenLists(1);

//    glEnableClientState( GL_VERTEX_ARRAY );
//    glEnableClientState( GL_TEXTURE_COORD_ARRAY );


}

void TexturedMesh::render()
{
    MaterialFaceLists::iterator matListIt;
    list<int>::iterator matFaceIt;

    // Compute transformation matrix
    computeMatrix();

    glPushMatrix();
    glMultMatrixf(m_transformation);

    for(matListIt = m_matFaceLists.begin(); matListIt != m_matFaceLists.end(); ++matListIt)
    {
        // Get list for current material
        MaterialFaceList* matList = *matListIt;

        // Get material
        Material* mat = m_materials[matList->m_matIndex];

        // Bind texture and set material properties
        if(mat->m_texture != 0)
        {
            mat->m_texture->bind();
        }
        setColorMaterial(mat->m_ambient, mat->m_diffuse, mat->m_specular, mat->m_shininess);

        // Render face group

        matFaceIt = matList->m_faces.begin();
        while(matFaceIt != matList->m_faces.end())
        {

            int a = *matFaceIt;
            ++matFaceIt;
            int b = *matFaceIt;
            ++matFaceIt;
            int c = *matFaceIt;
            ++matFaceIt;

            int a_pos = a * 3;
            int b_pos = b * 3;
            int c_pos = c * 3;

            int ta = a * 2;
            int tb = b * 2;
            int tc = c * 2;

            glBegin(GL_TRIANGLES);
            glTexCoord2f(m_textureCoords[ta], m_textureCoords[ta + 1]);
            glNormal3f(m_normalBuffer[a_pos], m_normalBuffer[a_pos + 1], m_normalBuffer[a_pos + 2]);
            glVertex3f(m_vertexBuffer[a_pos], m_vertexBuffer[a_pos + 1], m_vertexBuffer[a_pos + 2]);

            glTexCoord2f(m_textureCoords[tb], m_textureCoords[tb + 1]);
            glNormal3f(m_normalBuffer[b_pos], m_normalBuffer[b_pos + 1], m_normalBuffer[b_pos + 2]);
            glVertex3f(m_vertexBuffer[b_pos], m_vertexBuffer[b_pos + 1], m_vertexBuffer[b_pos + 2]);

            glTexCoord2f(m_textureCoords[tc], m_textureCoords[tc + 1]);
            glNormal3f(m_normalBuffer[c_pos], m_normalBuffer[c_pos + 1], m_normalBuffer[c_pos + 2]);
            glVertex3f(m_vertexBuffer[c_pos], m_vertexBuffer[c_pos + 1], m_vertexBuffer[c_pos + 2]);
            glEnd();
        }
    }

    glPopMatrix();

}

void TexturedMesh::setColorMaterial(Color &ambient, Color &diffuse, Color &specular, float shininess)
{
    GLfloat mat_specular[4] = {specular.r, specular.g, specular.b, 1.0};
    GLfloat mat_ambient[4]  = {ambient.r, ambient.g, ambient.b, 1.0};
    GLfloat mat_diffuse[4]  = {diffuse.r, diffuse.g, diffuse.b, 1.0};
    GLfloat mat_shininess[]  = {shininess};

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

}
