#include "view/HUD.hpp"
#include <QDebug>

HUD::HUD()
{
    //Fighter data
    fighterDamage 			  = 0;
    fighterSpeed  			  = 0; 
    fighterScore  			  = 0;
     
    durchmesser   			  = 150;
    abstand       			  = 10;
    paintLevel    			  = false;
    showCockpit   			  = false;
    showWarningCockpit       = 0;
    breite 		  			     = 0;
    hoehe 		  			     = 0;
    ShouldIdrawRedScreen     = 0;
    ShouldIdrawGreenScreen   = 0;
     
    //Init aller bilder
    cockpitImage              = QImage("res/images/cockpit.png");
    miniCraft    		         = QImage("res/images/ss.png");
    warningPic   		         = QImage("res/images/warning.png");
    redScreen    		         = QImage("res/images/redScreen.png");
    greenScreen  	            = QImage("res/images/greenScreen.png");
    WarningcockpitImage       = QImage("res/images/cockpitWarning.png");
    WarningcockpitBrokenImage = QImage("res/images/cockpitWarningBroken.png");
    cockpitBrokenImage        = QImage("res/images/cockpitBroken.png");
}

HUD::~HUD()
{

}

void HUD::setPainter(QPainter *paint)
{
    painter = paint;
}
void HUD::draw(int width, int height, QFont f)
{
	 //Updates the width and heigtht to the actual width and height
    breite = width;
    hoehe = height;
    
    if (showCockpit)
    {
    	  //move the Radar so Cockpit can be shown
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
    
    //draws level End if necessary
    if (paintLevel)
      	drawLevelEnd();

    //draws radar, score, speed and damage
    drawRadar();
    score(fighterScore);
    Speed(fighterSpeed);
    damages(fighterDamage);
    
    /*init a Vectoriterator used to iterate over the Vector which contains the
      position of the astroids*/ 
    std::vector<glVector<float>* >::iterator itervec;
    itervec = collvec.begin();
    
    //iterates over the vector and calls the draw method	
    if(!collvec.empty())
        while(itervec != collvec.end())
        {
            drawRadarAstroid(*itervec, 5000, durchmesser, radmidx, radmidy);
            ++itervec;
        }
}

void HUD::drawRadarAstroid(glVector<float>* vec, float radarrange, int durchmesser, int radarmidx, int radarmidy)
{
    //sets the Pen Color to Green
    painter->setPen(QColor(0,255,0,255));
    
    //Durchmesser der Elipse
    int p = 6;
    
    //constructs a copy of the vector to avoid Segmentfaults
    glVector<float> tmp(*vec);
    
    /*Every astroid astroid in the Range of 5000 will be painted in the center of the Radar.
    rest will be painted at the border*/
    if(vec->length() < 5000)
    {
    	  //scales the radarposition with a "three sentence(3 satz) "
        tmp.x /= radarrange;
        tmp.y /= radarrange;
        tmp.z /= radarrange;
        tmp = tmp * (durchmesser/2);
        
        //converts to int because ints are needed for draw Elipse/line
        int x = tmp.x;
        int y = tmp.y;
        int z = tmp.z;
        
        //Paints the astroid Red when its under the ship
        if(tmp.z < 0) painter->setPen(QColor(255,0,0,255));
        if(tmp.z != 0)
        {
        		/*draws the line which represents the height of the astroid to the ship. It might be
        		confusing that the radarx axis is the ship y axis*/  
            painter->drawLine(radarmidx + y, radarmidy + x, radarmidx + y,radarmidy + x -z);
        }
        // draws an Ellipse at the astroids Position
        painter->drawEllipse(radarmidx + y - (p/2), radarmidy + x - z - (p/2) ,p ,p);
    }
    else
    {
    	  //sets Pen color to red or green depending on the height of the astroid
    	  if(tmp.z >= 0)
        {   
             painter->setPen(QColor(0,255,0,255));
   	  }
        else
             painter->setPen(QColor(255,0,0,255));
        
        //sets the astroid on the border
        glVector<float> xytmp(tmp.x,tmp.y,0);
        xytmp.normalize();
        xytmp = xytmp * (durchmesser/2);
        
        //draws the astroid
        painter->drawEllipse(radarmidx+(xytmp.y)-(p/2), radarmidy+(xytmp.x)-(p/2),p,p);
    }
}
bool HUD::getView()
{
    return showCockpit;
}
void HUD::drawCockpit()
{
	//When the damages reaces 50 another cockpitimage wille be drawn
   if (fighterDamage >=50)
   {
   	 //showWarningCockpit works like a timer. The Warning will be dawn for 9 draw calls
       if ( (showWarningCockpit > 0) && (showWarningCockpit < 10) )
       {
       	   //increases showWarningCockpit and draws the image at the right spot
            showWarningCockpit++;
            WarningcockpitBrokenImage = WarningcockpitBrokenImage.scaledToWidth(breite);
            QPoint point = QPoint(0,hoehe-(WarningcockpitBrokenImage.size()).height());
            painter->drawImage(point, WarningcockpitBrokenImage);
       }
       else
       {
       	   //does the same but
            cockpitBrokenImage = cockpitBrokenImage.scaledToWidth(breite);
            QPoint point = QPoint(0,hoehe-(cockpitBrokenImage.size()).height());
            painter->drawImage(point, cockpitBrokenImage);
            //resetes the show warningCockpit
            showWarningCockpit = 0;
       }
    }
   else
   {
       //draws another picture
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
}

void HUD::setAstroidsVector(std::vector<glVector<float>* > collisionvec)
{
    collvec = collisionvec;
}

void HUD::score(int punkte)
{
    //sets Pen color to white
    painter->setPen(QColor(255,255,255,255));
    std::ostringstream Str;
    std::string pkt;

    //iteration veriable    
    int a;
    
    //starting Postion of the Array
    int stelle = 9;
    
    //temporary needed backup
    int tmp;
    
    //hard coded array
    int array[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    //puts the int in an array    
    while(punkte !=0)
    {
        //liest die erste stelle der zahl ein
        tmp = punkte % 10;
        punkte /= 10;
        
        a = stelle;
        array[stelle--] += tmp;
        //checks for ueberlauf        
        while(array[a] >= 10)
        {
        	   array[a] -= 10;
        	   array[--a]++;
        }
	 }
	 
	 //makes the array to a string
    for(int i = 0; i < 10 ;i++)
    {
        Str << array[i];
        pkt= ""+Str.str();
	 }
	 
    pkt = "SCORE : " + pkt;
    //draws the string
    QFont font("Atari Classic Chunky", 16, QFont::Bold);
    painter->setFont(font);
    QString aktuellepunkte = QString::fromStdString(pkt);
    QPoint point = QPoint(breite/2+30,30);
    painter->drawText(point,aktuellepunkte);
}

void HUD::damages(int schaden)
{
    //Sets pen color related to damage (green no damage -> red high damage)
    QPen pen(QColor((2.25)*schaden,255-((2.25)*schaden),0,200));
    pen.setWidth(9);
    painter->setPen(pen);
    
    //draws the arc
    QRectF rectangles(radmidx -(durchmesser/2)-10, radmidy-(durchmesser/2)-10, durchmesser+20, durchmesser+20);
    int startAngle = -50 * 16;
    int spanAngle = (100-schaden) * 16;
    painter->drawArc(rectangles, startAngle, spanAngle);
}

void HUD::Speed(float speed)
{
   //Sets pen color related to damage (green no damage -> red high damage)
 	QPen pen(QColor((2.25)*speed,255-((2.25)*speed),0,200));
 	pen.setWidth(9);
 	painter->setPen(pen);

	//draws the arc
 	QRectF rectangles(radmidx -(durchmesser/2)-10, radmidy-(durchmesser/2)-10, durchmesser+20, durchmesser+20);
 	int startAngle = 230 * 16;
 	int spanAngle = (-1)*speed * 16;
 	painter->drawArc(rectangles, startAngle, spanAngle);

}

void HUD::setFighterData(int damage, int score, float speed, bool shoot)
{
	//sets fighterdata
	if ( fighterDamage < damage )
	{
		//roten screen ausgeben
		ShouldIdrawRedScreen = 1;
	}
	if ( shoot )
	{
		//gruenen screen ausgeben
		ShouldIdrawGreenScreen = 1;
	}

    fighterDamage = damage;
    fighterScore = score;
    fighterSpeed = speed;
}

void HUD::drawRedScreen()
{
	//works like the Cockpitwarning but draws red screen
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
   //works like the Cockpitwarning but draws green screen
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
    //fills the Background with black
    painter->setBrush(QColor(0, 0, 0, 255));
    QRect rec(0,0,breite,hoehe);
    painter->drawRect(rec);

    //draws the image
    QImage myImage = QImage("res/images/splash.png");
    QPoint point = QPoint(breite/2 - myImage.width()/2,hoehe/2 - myImage.height()/2);
    painter->drawImage(point, myImage);
}
void HUD::drawRadar()
{
    //draws the Radar
    painter->setPen(QColor(255,255,255,255));
    painter->drawEllipse(radmidx - durchmesser/2, radmidy - durchmesser/2,durchmesser,durchmesser);
    painter->drawEllipse(radmidx - durchmesser/4, radmidy - durchmesser/4,durchmesser/2,durchmesser/2);

    //draws the "view" on the radar
    QRectF rectangle( radmidx-(durchmesser/2), radmidy-(durchmesser/2), durchmesser, durchmesser);
    painter->drawPie(rectangle, 45*16, 90*16);

    //draws the little ship on the radar
    QPoint point = QPoint(radmidx-15,radmidy-15);
    painter->drawImage(point, miniCraft);
}


void HUD::drawLevelEnd()
{
    painter->setPen(QColor(255,255,0,255));
    std::ostringstream Str;

    //draws the level Number
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
	//seperates between cockpit and "normal" modes
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
    //paints the background Black
    painter->setBrush(QColor(0, 0, 0, 255));
    QRect rec(0, 0, breite, hoehe);
    painter->drawRect(rec);
	 
	 //reads in the highscore and safes it in a vector
    ReadTXT *reader = new ReadTXT();
    vector<string> highscore = reader->read();
    vector<string>::iterator highIt;

    QString tmp;
    painter->setPen(QColor(255, 255, 255, 255));
    
    //the line of the highscore    
    int i = 0;
    
    //draws the highscore
	 highIt = highscore.begin();
	 QString header("-Highscore-");
    QPoint point = QPoint(100, 80);
    painter->drawText(point, header);
    while(highIt != highscore.end())
    {
    	  i++;
        tmp =  QString::fromStdString(*highIt);
        ++highIt;
        QPoint point2 = QPoint(100, 100 + 20 * i);
        painter->drawText(point2, tmp);
    }


}
void HUD::drawGameover(int breite, int hoehe)
{
    //fills the Background with black
    painter->setBrush(QColor(0, 0, 0, 255));
    QRect rec(0,0,breite,hoehe);
    painter->drawRect(rec);

    //paints the image
    QImage myImage = QImage("res/images/gameOver.png");
    QPoint point = QPoint(breite/2 - myImage.width()/2,hoehe/2 - myImage.height()/2);
    painter->drawImage(point, myImage);
}
