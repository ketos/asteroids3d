#include "view/HUD.hpp"

HUD::HUD()
{
	durchmesser = 150;
	abstand = 10;
	
}
void HUD::draw(QPainter *paint, int width, int height, QFont f)
{ 
        painter = paint;    
        radmidx = width/2;
        radmidy = height - (durchmesser/2) - abstand;
        


	     std::vector<glVector<float>* >::iterator itervec;
        itervec = collvec.begin();
        drawRadar(width,height);
        score(fighterScore,width/2,painter);
        Speed(fighterSpeed,0,painter);
        damages(fighterDamage,(width/2),painter);
    	
        while(itervec != collvec.end())
        {
            drawRadarAstroid(*itervec, 5000, durchmesser, width /2, height -(durchmesser / 2) - abstand, painter);	
                itervec++;
        }
     
}

void HUD::drawRadarAstroid(glVector<float>* vec, int radarrange, int durchmesser, int radarmidx, int radarmidy,QPainter *paint)
{
	     painter->setPen(QColor(0,255,0,255));
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
            paint->drawLine(radarmidx+x,radarmidy+(z),radarmidx+x,radarmidy+(-z)+y);
        paint->drawEllipse(radarmidx+x-(p/2), radarmidy-z+y-(p/2),p,p);
 

}

void HUD::setAstroidsVector(std::vector<glVector<float>* > collisionvec)
{
    collvec = collisionvec;
}

void HUD::score(int punkte, int breite, QPainter *painter)
{
    painter->setPen(QColor(255,255,255,255));
    std::ostringstream Str;
    Str << punkte;
    std::string pkt(Str.str());
    pkt = "SCORE : "+pkt;
    QFont font("Helvetica", 20, QFont::Bold);
    painter->setFont(font);
    QString aktuellepunkte = QString::fromStdString(pkt);
    QPoint point = QPoint(breite/2,30);
    painter->drawText(point,aktuellepunkte);
}

void HUD::damages(int schaden, int breite, QPainter *painter)
{
    
    painter->setPen(QColor(0,255,0,255));

  
    if(schaden>30)
    { 
        painter->setPen(QColor(255,255,0,255));
    }
    if(schaden>75){
        painter->setPen(QColor(255,0,0,255));}
    std::ostringstream Str;
    Str << schaden;
    std::string dmg("Schaden:"+Str.str()+"%");
    QFont font("Helvetica", 20, QFont::Bold);
    painter->setFont(font);
    QString leben = QString::fromStdString(dmg);
    QPoint point = QPoint(breite+50,30);
    painter->drawText(point,leben);
    
}


void HUD::Speed(float speed, int breite, QPainter *painter)
{
  
   painter->setPen(QColor(255,255,255,255));
   std::ostringstream Str;
   Str << speed;
  	std::string spd("Speed:"+Str.str()+"%");
  	QFont font("Helvetica", 20, QFont::Bold);
  	painter->setFont(font);
  	QString qspeed = QString::fromStdString(spd);
  	QPoint point = QPoint(0,30);
  	painter->drawText(point,qspeed);	
}


void HUD::setFighterData(int damage, int score, float speed)
{
	fighterDamage = damage;
	fighterScore = score;
	fighterSpeed = speed;
}

void HUD::drawSplash(int breite, int hoehe, QPainter *painter)
{
	QImage myImage = QImage("res/images/splash.png");
	myImage.load("res/images/splash.png");
	QPoint point = QPoint(breite/2 - myImage.width()/2,hoehe/2 - myImage.height()/2);
	painter->drawImage(point, myImage);
	
}
void HUD::drawRadar(int width, int height)
{
   painter->setPen(QColor(255,255,255,255));
   painter->drawEllipse(radmidx - durchmesser/2, radmidy - durchmesser/2,durchmesser,durchmesser);
   painter->drawEllipse(radmidx - durchmesser/4, radmidy - durchmesser/4,durchmesser/2,durchmesser/2);
        
   QRectF rectangle( (width/2)-(durchmesser/2), height-(durchmesser/2)-abstand-durchmesser/2, durchmesser, durchmesser);

   painter->drawPie(rectangle, 45*16, 90*16);
        
   QPoint point = QPoint(radmidx-15,radmidy-15);
   QImage myImage = QImage("res/images/ss.png");
   myImage.load("res/images/ss.png");
   painter->drawImage(point, myImage);	
}
