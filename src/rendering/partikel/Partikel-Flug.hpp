// Partikel für Flug

class PartikelFlug
{
public:
    //Konstruktor
    PartikelFlug(EmitterFlug* emit);
    //Destruktor
    ~PartikelFlug();

    //setzen der WErte
    void set(glVector<float> pos, glVector<float> speed,float size, glVector<float> color)

    // weitersetzen
    void update();
    //rendern
    void render();

    // Hole nächste Partikel
    Partikel* getNext();
    // setze nächsten Partikel
    void setNext(PartikelFlug* partikel);

private:
    //Gesundheitstatus
    bool m_alive;
    //Lebensdauer
    float m_lifetime;
    //Startzeit
    float m_birthday;
    //aktuelle Position
    glVector<float> m_position;
    //richtung
    glVector<float> m_speed;
    //grösse
    float m_size;
    //Farbe
    glVector<float<m_Color;
    //Emitter
    EmitterFlug* m_emit; 
    //nächster Partikel
    PartikelFlug* m_Next;
    
};

class PartikelList :public CList<PartikelFlug*> {};
