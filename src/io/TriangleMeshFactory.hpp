/**
 * TriangleMeshFactory.hpp
 *
 *  @date 10.12.2011
 *  @author Thomas Wiemann
 */

#ifndef TRIANGLEMESHFACTORY_H_
#define TRIANGLEMESHFACTORY_H_

#include <string>
#include "rendering/TriangleMesh.hpp"

using std::string;

/**
 * @brief   A factory class for loading triangle meshes. Implements to
 *          factory design pattern
 */
class TriangleMeshFactory
{
protected:

    /**
     * @brief Constructor
     */
    TriangleMeshFactory() {};

    /**
     * @brief Destructor
     */
    virtual ~TriangleMeshFactory() {};

public:

    /**
     * @brief Returns the mesh parsed from the file or a null pointer
     *        if an error occured
     */
    TriangleMesh* getMesh(const string &filename) const;

    /**
     * @brief Returns the instance pointer of the factory singleton
     */
    static TriangleMeshFactory& instance();

};

#endif /* TRIANGLEMESHFACTORY_H_ */
