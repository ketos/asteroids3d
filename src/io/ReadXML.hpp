#ifndef __READXML_HPP__
#define __READXML_HPP__

#include "math/glVector.hpp"
#include <Qt>
#include <QDomDocument>
#include <QFile>
#include <QIODevice>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using std::string;
using std::vector;

/**
 * @brief XML parser für die Level.xml's
 */
class ReadXML
{
public:

    /**
     * @brief    Liest xml-files ein und gibt Inhalt zurück 
     *
     * @param    filename		Name des einzulesenden xml-files
     *
     * @return   vector<std::pair<glVector<float>*, glVector<float>* >* >
     *           vector, bestehend aus glVector pairs, welche postion und axis
     *           der Asteroiden beinhalten	 
     */
    static vector<std::pair<glVector<float>*, glVector<float>* >* >* readConfig(string& filename);
   
};

#endif // __READXML_HPP__
