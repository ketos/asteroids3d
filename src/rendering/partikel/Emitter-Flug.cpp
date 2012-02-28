// http://www.codeworx.org/opengl_par1.php

//Emitter für Flug

EmitterFlug::EmitterFlug(int Partikelanzahl)
{
    m_maxPartikel  = Partikelanzahl;
    m_PartikelZahl = 0;
}

EmitterFlug::~EmitterFlug()
{
    //TODO alle Partikel löschen
}

void EmitterFlug::update()
{   
    //Erstes Partikel
    PartikelFlug* pPar = m_partikel.GetHead();
    //Folgendes Partikel
    PartikelFlug* pPrev= NULL;
    //durchgehen
    while(pPar)
    {   
        //updaten
        pPar->update();
        //alive abfragen
        if(!pPar->m_alive) //wenn nicht mehr am Leben
        {
            if(pPrev)
            {
                
                pPrev->setNext(pPar->getNext());
            } else 
            {
                m_partikel.setHead(pPar->getNext());
            } 
            // Partikel löschen und anzahl verringern  
            delete pPar;
            pPar = Null;
            m_PartikelZahl--;

            if(pPrev)
            {
                pPar = pPrev->getNext();
            } else 
            {
                pPar = m_partikel.getHead();
            }
            continue; // nächster Schleifenaufruf
        } else
        {   
            //wenn alive rendern;
            pPar->render();
        }
        //weitergehen;
        pPrev = pPar;
        pPar = pPar->getNext();
    }
}

bool EmitterFlug::add(PartikelFlug* partikel)
{   
    //wenn noch Platz
    if(m_PartikelZahl < m_maxPartikel)
    {   
        //Füge hinzu
        m_partikel.Add(partikel);
        //erhöhe Anzahl
        m_PartikelZahl++;
        //gebe erstellt zurück
        return true;
    }
    //gebe nicht erstellt zurück
    return false;
}
