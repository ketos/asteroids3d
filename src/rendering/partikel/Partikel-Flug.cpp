

PartikelFlug::PartikelFlug(EmitterFlug* emit)
{
    m_emit = emit;
    m_alive = true;
    m_next = NULL;
    //m_birthday setzen
}

PartikelFlug::~PartikelFlug()
{

}

void PartikelFlug::set(float lifetime,
                       glVector<float> pos, 
                       glVector<float> speed,
                       float size, 
                       glVector<float> color)
{
    m_lifetime = lifetime;
    m_position = pos;
    m_speed    = speed;
    m_size     = size;
    m_Color    = color;
}

Partikel* PartikelFlug::getNext()
{
    return m_next;
}
    
void PartikelFlug::setNext(PartikelFlug* partikel)
{
    m_next = partikel;
}

void PartikelFlug::update()
{
    //wenn lebensdauer überschritten
    if(m_emit->m_fCurTime - m_fbirthday > m_lifetime)
    {   
        //töten
        m_alive = false;
        return
    }
    //weitersetzen
    m_position += (m_speed * (m_emit->m_fFrameTime));
}

void PartikelFlug::render()
{
    //hier rendern
    //glusphere?
}
