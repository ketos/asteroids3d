/**
 * MeshIO.h
 *
 *  @date 10.12.2011
 *  @author Thomas Wiemann
 */

#ifndef MESHIO_H_
#define MESHIO_H_

#include "rendering/TriangleMesh.hpp"

class MeshIO
{
public:
    MeshIO()
        : m_vertexBuffer(0),
          m_normalBuffer(0),
          m_indexBuffer(0),
          m_numVertices(0),
          m_numFaces(0) {};


    virtual ~MeshIO() {};

    virtual TriangleMesh* getMesh() = 0;

protected:
    float*  m_vertexBuffer;
    float*  m_normalBuffer;
    int*    m_indexBuffer;

    int     m_numVertices;
    int     m_numFaces;
};

#endif /* MESHIO_H_ */
