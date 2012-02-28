// http://www.codeworx.org/opengl_par1.php

//Emitter für Flug

class EmitterFlug
{
public:
    //Konstruktor
    EmitterFlug(int Partikelanzahl);
    //Destruktor
    ~EmitterFlug();

    //returnt aktuelle Zahl an Partikeln
    int getaktPartikelzahl();
    //neuer Partikel hinzufügen
    bool add(PartikelFlug* partikel);
    // alle updaten
    void update();
    
    static float m_fFrameTime;
    static float m_fCurTime;

private:
    //alle Partikel
    PartikelList m_partikel;
    //aktuelle Anzahl von Partikeln
    int m_PartikelZahl;
    //Maximale Anzahl an Partikeln
    int m_maxPartikel
}
