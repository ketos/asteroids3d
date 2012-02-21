#include "view/HUD.hpp"

void HUD::draw(QPainter *painter,int x, int y, QFont f)
{

    int width  = x;
    int height = y; 
     //std::string dmg = "Schaden "+m_fighter.getDamage()+"%";
     //std::string points = "Punkte "+m_fighter.getPoints();
     std::string dmg = "Schaden 0%";
     QString damage = QString::fromStdString(dmg);
     QFontMetrics metrics = QFontMetrics(f);
     int border = qMax(4, metrics.leading());

     QRect rect = metrics.boundingRect(0, 0, width - 2*border, int(height*0.125),
                                       Qt::AlignCenter | Qt::TextWordWrap, damage);
     painter->setRenderHint(QPainter::TextAntialiasing);
     painter->fillRect(QRect(0, height-50, 100, 50),
                      QColor(255, 0, 0, 127));
     painter->setPen(Qt::white);
     painter->fillRect(QRect(0,height-50, 100 ,50),
                       QColor(0, 0, 0, 127));
     painter->drawText(20, height-30,
                       rect.width(), rect.height(),
                       Qt::AlignCenter | Qt::TextWordWrap, damage);
     painter->drawLine(width/2, height-10, width/2, height-110);
     painter->drawLine((width/2)-50, height-60, (width/2)+50, height-60);
     painter->drawLine((width/2)-25, height-30, (width/2)+25, height-90);
   //QPoint point = QPoint(width()/2,height()-236);
   //QImage myImage =QImage("radar.gif");
   //myImage.load("mb.png");
   //painter->drawImage(point, myImage);
}

