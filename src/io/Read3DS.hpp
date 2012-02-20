/**
 * Read3DS.hpp
 *
 *  @date 10.12.2011
 *  @author Thomas Wiemann
 */

#ifndef READ3DS_HPP_
#define READ3DS_HPP_

#include "rendering/TriangleMesh.hpp"
#include "rendering/TexturedMesh.hpp"
#include "rendering/Materials.hpp"

#include "MeshIO.hpp"
#include "TextureFactory.hpp"

#include <string>
#include <vector>
using std::vector;
using std::string;

class Read3DS : public MeshIO
{
public:
    Read3DS(std::string filename);

    TriangleMesh* getMesh();

    void getMesh(TexturedMesh &texMesh);

    virtual ~Read3DS();

private:

    void readSimpleMesh();
    void readTexturedMesh();

    string m_filename;
};

#endif /* READ3DS_HPP_ */
