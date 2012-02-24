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
    static void readConfig(string& filename);
    
    /**
     * @brief Gibt die pair-Liste aller eingelesenen Asterioden zurück
     */
    static vector<std::pair<glVector<float>, glVector<float> > > getAsteroids();
  
private:

    /**
     * @brief pair-Liste aller eingelesenen Asterioden
     */
    static vector<std::pair<glVector<float>, glVector<float> > > m_asteroidList;
};

#endif // __READXML_HPP__
