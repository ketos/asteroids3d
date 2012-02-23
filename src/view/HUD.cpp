#include "view/HUD.hpp"
void HUD::draw(QPainter *painter, int width, int height, QFont f)
{ 
              
        int durchmesser = 150;
        int abstand = 10;
        
        int radmidx = width/2;
        int radmidy = height - (durchmesser/2) - abstand;
        
        //painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter->fillRect(width/2-(durchmesser/2), height-abstand-(durchmesser*1.5),durchmesser,durchmesser*1.5,QColor(255, 0, 0, 0));
        //painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

        //Schadensanzeige
        std::string dmg = "Schaden 0%";
        QString damage = QString::fromStdString(dmg);
        QFontMetrics metrics = QFontMetrics(f);
        int border = qMax(4, metrics.leading());

        QRect rect = metrics.boundingRect(0, 0, width - 2*border, int(height*0.125),Qt::AlignCenter | Qt::TextWordWrap, damage);
        painter->setRenderHint(QPainter::TextAntialiasing);
        painter->fillRect(QRect(0, height-50, 100, 50),QColor(255, 0, 0, 127));
        painter->setPen(Qt::white);
        painter->fillRect(QRect(0,height-50, 100 ,50),
                       QColor(0, 0, 0, 127));
        painter->drawText(20, height-30,rect.width(), rect.height(),
                       Qt::AlignCenter | Qt::TextWordWrap, damage);


        //Radar
        painter->drawEllipse(radmidx - durchmesser/2, radmidy - durchmesser/2,durchmesser,durchmesser);
        painter->drawEllipse(radmidx - durchmesser/4, radmidy - durchmesser/4,durchmesser/2,durchmesser/2);
        
        QRectF rectangle( (width/2)-(durchmesser/2), height-(durchmesser/2)-abstand-durchmesser/2, durchmesser, durchmesser);
        
        int startAngle = 45 * 16;
        int spanAngle = 90 * 16;
        painter->drawPie(rectangle, startAngle, spanAngle);
        
        QPoint point = QPoint(radmidx-15,radmidy-15);
        QImage myImage =QImage("ss.png");
        myImage.load("ss.png");
        painter->drawImage(point, myImage);

	std::vector<glVector<float>* >::iterator itervec;
        itervec = collvec.begin();

        //vector<glVector<float> >::iterator itervec; 
        glVector<float> huas(5000,-30000,12300);

        while(itervec != collvec.end())
        {
            drawRadarAstroid(*itervec, 5000, durchmesser, width /2, height -(durchmesser / 2) - abstand, painter);
		itervec++;
        }
     
}

void HUD::drawRadarAstroid(glVector<float>* vec, int radarrange, int durchmesser, int radarmidx, int radarmidy,QPainter *paint)
{
        int p = 6;
	glVector<float> tmp(*vec);
        tmp.x/=radarrange;
        tmp.y/=radarrange;
        tmp.z/=radarrange;
        tmp =/* (vec*(1/radarrange))*/tmp * (durchmesser/2);
        int x = tmp.x;
        int y = tmp.y;
        int z = tmp.z;

        if(!tmp.y == 0)
            paint->drawLine(radarmidx+x,radarmidy+(z),radarmidx+x,radarmidy+(z)+y);
        paint->drawEllipse(radarmidx+x-(p/2), radarmidy+z+y-(p/2),p,p);

}

void HUD::setAstroidsVector(std::vector<glVector<float>* > collisionvec)
{
    collvec = collisionvec;
}
