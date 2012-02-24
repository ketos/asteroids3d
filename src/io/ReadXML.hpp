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
 * @brief XML parser für die Spiel config
 */
class ReadXML
{
public:

    /**
     * @brief Liest config.xml ein un  fügt Asteroiden daten der Liste hinzu
     */
    static vector<std::pair<glVector<float>*, glVector<float>* >* > readConfig(string& filename);
    
  
private:

    /**
     * @brief pair-Liste aller eingelesenen Asterioden
     */
    
};

#endif // __READXML_HPP__
