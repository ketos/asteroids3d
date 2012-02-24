#include "ReadXML.hpp"

vector<std::pair<glVector<float>*, glVector<float>* >* >  ReadXML::readConfig (string& filename)
{
	vector<std::pair<glVector<float>*, glVector<float>* >* > m_asteroidList;
	
 	QDomDocument doc("level");
    //QFile file("config.xml");
    
    //if(!file.open(QIODevice::ReadOnly))
    //{
        
    //}    
    //if( !doc.setContent(&file))
    //{
    //    file.close();
 
    //}
    //file.close();
    
    glVector<float>* pos; 
    glVector<float>* axis;
    std::pair<glVector<float>*,glVector<float>*>* p;
    
    QDomNode level   = doc.documentElement();
    QDomNode asteroid    = level.firstChild();
    QDomElement ad;
    
    while(!asteroid.isNull())
    {
        ad = asteroid.toElement();
        
        pos  = new glVector<float>(ad.attribute("pos_x","").toFloat(),
                                   ad.attribute("pos_y","").toFloat(),
                                   ad.attribute("pos_z","").toFloat());
                       
        axis = new glVector<float>(ad.attribute("axis_x","").toFloat(),
                        	       ad.attribute("axis_y","").toFloat(),
                                   ad.attribute("axis_z","").toFloat());               
        p->first   = pos;
        p->second  = axis;
        m_asteroidList.push_back(p); 
        
        asteroid = asteroid.nextSibling();                            
    } 
    return m_asteroidList;
}

    
                
     
    
    





