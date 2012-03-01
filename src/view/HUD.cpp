#include "view/HUD.hpp"
#include <QDebug>
HUD::HUD()
{
	fighterDamage 			= 0;
	fighterSpeed  			= 0;
	fighterScore  			= 0;
	durchmesser   			= 150;
	abstand       			= 10;
	paintLevel    			= false;
	showCockpit   			= false;
	showWarningCockpit 		= 0;
	breite 		  			= 0;
	hoehe 		  			= 0; 
	ShouldIdrawRedScreen    = 0;
	ShouldIdrawGreenScreen  = 0;
	
	//ini aller bilder
	cockpitImage    	= QImage("res/images/cockpit.png");
	miniCraft    		= QImage("res/images/ss.png");
    warningPic   		= QImage("res/images/warning.png");
    redScreen    		= QImage("res/images/redScreen.png");
    greenScreen  		= QImage("res/images/greenScreen.png");
    WarningcockpitImage = QImage("res/images/cockpitWarning.png");
}

HUD::~HUD()
{
    delete &cockpitImage;
    delete &miniCraft;
    delete &warningPic;
    delete &redScreen;
    delete &greenScreen;
    delete &WarningcockpitImage;
}

void HUD::setPainter(QPainter *paint)
{
	painter       = paint;
}
void HUD::draw(int width, int height, QFont f)
{    
	breite = width;
	hoehe = height;
    // radar für 3.person verschieben	
	if (showCockpit)
	{
		radmidx = width  - (durchmesser/2) - 40;
    	radmidy = height - (height-(durchmesser/2)) + 40;
	}
	else
	{
		radmidx = width/2;
    	radmidy = height - (durchmesser/2) - abstand;
	}
    
    //draw events like redscreen
    drawRedScreen();
    drawGreenScreen();
    //draw cockpit if necessary
    if (showCockpit)
    {
    	//draw Cockpit
    	drawCockpit();	
    }
    if (paintLevel)
      	drawLevelEnd();
	 std::vector<glVector<float>* >::iterator itervec;
    itervec = collvec.begin();
    drawRadar(width,height);
    score(fighterScore,width/2);
    Speed(fighterSpeed);
    damages(fighterDamage);

    	
    if(!collvec.empty())
    	while(itervec != collvec.end())
        {
            drawRadarAstroid(*itervec, 5000, durchmesser, radmidx, radmidy);	
            itervec++;
        }
     
}

void HUD::drawRadarAstroid(glVector<float>* vec, float radarrange, int durchmesser, int radarmidx, int radarmidy)
{
	painter->setPen(QColor(0,255,0,255));
    int p = 6;
	glVector<float> tmp(*vec);
	if(vec->length()<5000)
	{
	   tmp.x/=radarrange;
       tmp.y/=radarrange;
       tmp.z/=radarrange;
       tmp = tmp * (durchmesser/2);
       int x = tmp.x;
       int y = tmp.y;
       int z = tmp.z;
        if(tmp.z < 0) painter->setPen(QColor(255,0,0,255));
       if(tmp.z != 0){
           painter->drawLine(radarmidx+y,radarmidy+(x),radarmidx+y,radarmidy+x-z);
       }
        
       painter->drawEllipse(radarmidx+y-(p/2), radarmidy+x-z-(p/2),p,p);
   }
   else{
   	if(tmp.z>=0)
   	{
   		painter->setPen(QColor(0,255,0,255));
   	}else
   		painter->setPen(QColor(255,0,0,255));
   	glVector<float> xytmp(tmp.x,tmp.y,0);
		xytmp.normalize();
		xytmp = xytmp * (durchmesser/2);
		painter->drawEllipse(radarmidx+(xytmp.y)-(p/2), radarmidy+(xytmp.x)-(p/2),p,p); 	
  	}
}
bool HUD::getView()
{
	return showCockpit;
}
void HUD::drawCockpit()
{
	if ( (showWarningCockpit > 0) && (showWarningCockpit < 10) )
	{
		showWarningCockpit++;
		WarningcockpitImage = WarningcockpitImage.scaledToWidth(breite);
        QPoint point = QPoint(0,hoehe-(WarningcockpitImage.size()).height());
        painter->drawImage(point, WarningcockpitImage);
	}
	else
	{
		cockpitImage = cockpitImage.scaledToWidth(breite);
        QPoint point = QPoint(0,hoehe-(cockpitImage.size()).height());
        painter->drawImage(point, cockpitImage);
        showWarningCockpit = 0;
	}
}	

void HUD::setAstroidsVector(std::vector<glVector<float>* > collisionvec)
{
    collvec = collisionvec;
}

void HUD::score(int punkte, int breite)
{
	painter->setPen(QColor(255,255,255,255));
    std::ostringstream Str;

    std::string pkt;
	int a;
	int stelle = 9;
	int tmp;
	int array[]={0,0,0,0,0,0,0,0,0,0};
	while(punkte !=0)
	{
		tmp = punkte % 10;
		punkte /= 10;
		array[stelle--] += tmp;
		a = stelle + 1; 
		while(array[a] >= 10)
		{
			array[a] -= 10;
			array[--a]++;	
		} 
	}
	for(int i = 0; i < 10 ;i++)
	{
		   Str << array[i];
		   pkt= ""+Str.str();
		
	}
    pkt = "SCORE : "+pkt;
    QFont font("Atari Classic Chunky", 16, QFont::Bold);
    painter->setFont(font);
    QString aktuellepunkte = QString::fromStdString(pkt);
    QPoint point = QPoint(breite/2+30,30);
    painter->drawText(point,aktuellepunkte);
}

void HUD::damages(int schaden)
{
 	 QPen pen(QColor((2.25)*schaden,255-((2.25)*schaden),0,200));
     pen.setWidth(9);
 	 painter->setPen(pen);
 	 
	 QRectF rectangles(radmidx -(durchmesser/2)-10, radmidy-(durchmesser/2)-10, durchmesser+20, durchmesser+20);
 	 int startAngle = -50 * 16;
 	 int spanAngle = (100-schaden) * 16;
    painter->drawArc(rectangles, startAngle, spanAngle);    
}

void HUD::Speed(float speed)
{

 	QPen pen(QColor((2.25)*speed,255-((2.25)*speed),0,200));
    //pen.setStyle(Qt::DashDotLine);
    pen.setWidth(9);
 	painter->setPen(pen);
 	
 	QRectF rectangles(radmidx -(durchmesser/2)-10, radmidy-(durchmesser/2)-10, durchmesser+20, durchmesser+20);
 	int startAngle = 230 * 16;
 	int spanAngle = (-1)*speed * 16;
 	painter->drawArc(rectangles, startAngle, spanAngle);

}

void HUD::setFighterData(int damage, int score, float speed, bool shoot)
{
	if ( fighterDamage < damage )
	{
		//roten screen ausgeben
		ShouldIdrawRedScreen = 1;
	}
	if ( shoot )
	{
		ShouldIdrawGreenScreen = 1;
	}
	
    fighterDamage = damage;    
    fighterScore = score;
    fighterSpeed = speed;
}

void HUD::drawRedScreen()
{
	if ( (ShouldIdrawRedScreen < 10	) && (ShouldIdrawRedScreen > 0) )
	{
		ShouldIdrawRedScreen++;
		//printen des redscreen
		redScreen = redScreen.scaled(breite,hoehe);
    	QPoint point = QPoint(0,0);
    	painter->drawImage(point, redScreen);
	}
	else
	{
		ShouldIdrawRedScreen = 0;
	}	
}
void HUD::drawGreenScreen()
{
	if ( (ShouldIdrawGreenScreen < 5) && (ShouldIdrawGreenScreen > 0) )
	{
		ShouldIdrawGreenScreen++;
		//printen des redscreen
		greenScreen = greenScreen.scaled(breite,hoehe);
    	QPoint point = QPoint(0,0);
    	painter->drawImage(point, greenScreen);
	}
	else
	{
		ShouldIdrawGreenScreen = 0;
	}	
}
void HUD::drawSplash(int breite, int hoehe)
{
	 painter->setBrush(QColor(0, 0, 0, 255));
	 QRect rec(0,0,breite,hoehe);
	 painter->drawRect(rec);  
	
    QImage myImage = QImage("res/images/splash.png");
    QPoint point = QPoint(breite/2 - myImage.width()/2,hoehe/2 - myImage.height()/2);
    painter->drawImage(point, myImage);
}
void HUD::drawRadar(int width, int height)
{
    painter->setPen(QColor(255,255,255,255));
    painter->drawEllipse(radmidx - durchmesser/2, radmidy - durchmesser/2,durchmesser,durchmesser);
    painter->drawEllipse(radmidx - durchmesser/4, radmidy - durchmesser/4,durchmesser/2,durchmesser/2);
	
	QRectF rectangle( radmidx-(durchmesser/2), radmidy-(durchmesser/2), durchmesser, durchmesser);

    painter->drawPie(rectangle, 45*16, 90*16);

    QPoint point = QPoint(radmidx-15,radmidy-15);
    painter->drawImage(point, miniCraft);	
}


void HUD::drawLevelEnd()
{	
    painter->setPen(QColor(255,255,0,255));
    std::ostringstream Str;
    
    Str << levelNumber;
    std::string spd("Level: " + Str.str());
    QFont font("Atari Classic Chunky", 40, QFont::Bold);
    painter->setFont(font);
    QString qspeed = QString::fromStdString(spd);
    QPoint point2 = QPoint(0, 100);
    painter->drawText(point2,qspeed);
}

void HUD::setIncLevel(bool shouldIPaint)
{
    paintLevel = shouldIPaint;
}

void HUD::setLevel(int levelnumber)
{
    levelNumber = levelnumber;
}

void HUD::drawWarning()
{
	if (showCockpit)
	{
		showWarningCockpit = 1;	
	}
	else
	{
    	QPoint point = QPoint(abstand,hoehe - (warningPic.height() + abstand) );
    	painter->drawImage(point, warningPic);
    }
}

void HUD::loadCockpit()
{
	showCockpit = true;
}

void HUD::deleteCockpit()
{
	showCockpit = false;
}
void HUD::drawHighscore()
{
	
	std::cout<<"Ich male die Score"<<std::endl;
	painter->setBrush(QColor(0, 0, 0, 255));
	QRect rec(0,0,breite,hoehe);
    painter->drawRect(rec); 
	ReadTXT *reader = new ReadTXT();
    vector<string> highscore = reader->read();
    vector<string>::iterator highIt;
    
    QString tmp;
    painter->setPen(QColor(255,255,255,255));
int i=0;
	highIt = highscore.begin();
    while(highIt != highscore.end())
    {
    	i++;
        tmp =  QString::fromStdString(*highIt); 
        highIt++;
        QPoint point2 = QPoint(breite/2, 100+20*i);
   	  painter->drawText(point2,tmp);
    }

	
}
