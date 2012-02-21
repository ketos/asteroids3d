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

class HUD{
public:
    void draw(QPainter *painter,int x ,int y, QFont f);
    //static HUD getInstance();
    //static void destroy();
    
private:
    ///HUD();
    //HUD(const HUD&);
    //~HUD();
    //static HUD* instance;
    
};

#endif //_HUD_H
