#include "ReadXML.hpp"

vector<std::pair< glVector<float>, glVector<float> > > ReadXML::m_asteroidList = 0;

void ReadXML::readConfig (string& filename)
{
    QDomDocument doc("asteroids");
    QFile file("config.xml");
    
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }    
    if( !doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    
    glVector<float> pos, axis;
    
    QDomNode asteroids   = doc.documentElement();
    QDomNode asteroid    = asteroids.firstChild();
    QDomElement ad;
    
    while(!asteroid.isNull())
    {
        ad = asteroid.toElement();
        
        pos  = glVector<float>(ad.attribute("pos_x","").toFloat(),
                        ad.attribute("pos_y","").toFloat(),
                        ad.attribute("pos_z","").toFloat());
                       
        axis = glVector<float>(ad.attribute("axis_x","").toFloat(),
                        ad.attribute("axis_y","").toFloat(),
                        ad.attribute("axis_z","").toFloat());               
                        
        m_asteroidList->push_back(std::make_pair(pos, axis)); 
        
        asteroid = asteroid.nextSibling();                            
    } 
}

vector<std::pair<glVector<float>, glVector<float> > > ReadXML::getAsteroids()
{
    return m_asteroidList;
}    
    
    
                
     
    
    





