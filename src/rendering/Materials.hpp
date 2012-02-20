/**
 * Materials.hpp
 *
 *  @date 13.12.2011
 *  @author Thomas Wiemann
 */

#ifndef MATERIALS_HPP_
#define MATERIALS_HPP_

#include <list>
using std::list;

class Texture;

struct Color
{
    Color() : r(125), g(125), b(125) {};
    float r;
    float g;
    float b;
};

struct TexCoord
{
    float u;
    float v;
};

struct Material
{
    Color       m_ambient;
    Color       m_diffuse;
    Color       m_specular;
    float       m_shininess;
    Texture*    m_texture;
};

struct MaterialFaceList
{
    int         m_matIndex;
    list<int>   m_faces;
};

typedef list<MaterialFaceList*> MaterialFaceLists;

#endif /* MATERIALS_HPP_ */
