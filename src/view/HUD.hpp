#ifndef _HUD_H
#define _HUD_H

#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QGLWidget>
#include <QString>
#include <string.h>
#include <QFontMetrics>
#include "math/glVector.hpp"
#include <vector>

class HUD{
public:
    void draw(QPainter *painter,int x ,int y, QFont f);
    void drawRadarAstroid(glVector<float>* vec, int radarrange, int durchmesser, int radarmidx, int radarmidy,QPainter *paint);
    //static HUD getInstance();
    //static void destroy();
    void setAstroidsVector(std::vector<glVector<float>* > collvec);
    
private:
    ///HUD();
    //HUD(const HUD&);
    //~HUD();
    //static HUD* instance;

    std::vector<glVector<float>* > collvec;
    
};

#endif //_HUD_H
