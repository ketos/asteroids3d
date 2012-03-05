#include "ReadXML.hpp"

vector<pair<glVector<float>*, glVector<float>* >* >*  ReadXML::readConfig (string& filename)
{
    // Deklarieung der vector Liste
    vector<pair<glVector<float>*, glVector<float>* >* > *m_asteroidList = new vector<pair<glVector<float>*, glVector<float>* >* >();
	
    QDomDocument doc("level");
    QString s(filename.c_str());
    QFile file(s);
    
    // Fehlerbehandlung, sofern file nicht geöffnet werden kann 
    if(!file.open(QIODevice::ReadOnly))
    {
   	    std::cout << "Fehler: Datei kann nicht eingelesen werden" <<std::endl;
    }
       
    // Öffnen und Schliessen des files   
    if( !doc.setContent(&file))
    {
   	    file.close();
    }
   
    file.close();

    // glVector pointer für die Startposition des Asteroiden
    glVector<float>* pos; 
    // glVector pointer für die Flugrichtung und -geschwindigkeit des Asteroiden
    glVector<float>* axis;
    // glVector pair poiner für die beiden vectoren
    std::pair<glVector<float>*,glVector<float>*>* p;
    
    // Baumsruktur des .xmls wird durchlaufen
    QDomNode level    = doc.documentElement();
    QDomNode asteroid = level.firstChild();
    QDomElement ad;
    
    /**
     * ein "Asteroidenelement" wird durchlaufen, alle seine Attribute in floats 
     * umgewandelt und in m_asteroidList eingefügt
     */ 
    while(!asteroid.isNull())
    {
   	    ad = asteroid.toElement();

        pos  = new glVector<float>( ad.attribute("pos_x","0").toFloat(),
                                    ad.attribute("pos_y","0").toFloat(),
                                    ad.attribute("pos_z","0").toFloat() );
                                   
        axis = new glVector<float>( ad.attribute("axis_x","0").toFloat(),
                      	            ad.attribute("axis_y","0").toFloat(),
                                    ad.attribute("axis_z","0").toFloat() );
                                   
        p = new pair<glVector<float>*, glVector<float>*>();            

        p->first  = pos;
        p->second = axis;
        
        m_asteroidList->push_back(p); 
        
        // nächster Geschwisterknoten wird druchlaufen, sofern vorhanden
        asteroid = asteroid.nextSibling();                            
    } 

    return m_asteroidList;
}