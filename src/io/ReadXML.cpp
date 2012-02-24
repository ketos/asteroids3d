#include "ReadXML.hpp"

vector<std::pair<glVector<float>*, glVector<float>* >* >*  ReadXML::readConfig (string& filename)
{
	std::cout <<"im xlreader : "<< filename <<std::endl;
	vector<std::pair<glVector<float>*, glVector<float>* >* > *m_asteroidList = new vector<std::pair<glVector<float>*, glVector<float>* >* >();
	
 	QDomDocument doc("level");
    QFile file("config.xml");
    
    if(!file.open(QIODevice::ReadOnly))
    {
    	std::cout << "Fehler: Datei nicht zu lesen "<<std::endl;

    }    
    if( !doc.setContent(&file))
    {
        file.close();
 
    }
    file.close();

    glVector<float>* pos; 
    glVector<float>* axis;
    std::pair<glVector<float>*,glVector<float>*>* p;
    std::cout <<"xlreader spaeter " <<std::endl;
    
    QDomNode level       = doc.documentElement();
    QDomNode asteroid    = level.firstChild();
    QDomElement ad;
    
    /**
    * ein Asteroid wird durchlaufen, alle seine Attribute in floats umgewandelt
    * und in m_asteroidList eingefügt
    */ 
    while(!asteroid.isNull())
    {
    	std::cout <<"xmlreader schleife " <<std::endl;
        ad = asteroid.toElement();

        pos  = new glVector<float>(ad.attribute("pos_x","0").toFloat(),
                                   ad.attribute("pos_y","0").toFloat(),
                                   ad.attribute("pos_z","0").toFloat());
        //std::cout << "posx" << ad.attribute("pos_x","").toFloat()<<" " << ad.attribute("pos_y","").toFloat() << " " <<ad.attribute("pos_z","").toFloat() << std::endl;
        axis = new glVector<float>(ad.attribute("axis_x","0").toFloat(),
                        	       ad.attribute("axis_y","0").toFloat(),
                                   ad.attribute("axis_z","0").toFloat());
                                   
        p = new std::pair<glVector<float>*, glVector<float>*>();            

        p->first   = pos;
        p->second  = axis;
        
        std::cout << "p->first->x " << p->first->x << std::endl;
        m_asteroidList->push_back(p); 
        
        asteroid = asteroid.nextSibling();                            
    } 
    std::cout << "end reader "<< std::endl;

    return m_asteroidList;
}

    
                

    
    





