#include "RenderFrame.hpp"

#include <set>

#include <QKeyEvent>
#include <QMouseEvent>

#include "rendering/TexturedMesh.hpp"
#include "rendering/Fighter.hpp"
#include "math/glVector.hpp"
#include "io/Read3DS.hpp"
#include "rendering/Asteorid.hpp"
#include <stdio.h>
// sudo apt-get install joystick   ausführen
#include "io/SoundManager.hpp"

#include <string>

#include "view/Menu.hpp"


Camera RenderFrame::m_cam;
bool RenderFrame::shoot;
bool menu = false; 
bool warning_sound = false;

RenderFrame::RenderFrame(QWidget* parent) : QGLWidget(parent)
{
    
    // set up animation timer
    m_timer = new QTimer();
    m_timer->setInterval(25);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()),Qt::QueuedConnection);
    
    shoot = true;
    
    reload = 0;
    
    joys = new JoystickControl("/dev/input/js0");
    
    joystick = joys->connected();

	setAutoFillBackground(false);

    show();
    menu = true;
    RenderFrame::paintHighscore = false;
}

RenderFrame::~RenderFrame()
{
    if(joystick)
    {
        delete joys;
    }
    delete Game::getFighter();
    delete m_skybox;
    SoundManager::deleteManager();
}

void RenderFrame::start()
{
    menu = false;
    Menu::deleteSplash();
    
    Game::Init();

    Game::getCollision()->start();
    
    // start Timer
    m_timer->start();
}

void RenderFrame::initializeGL()
{

	// Create a sky box
	string names[6];
	names[0] = "box1.ppm";
	names[1] = "box2.ppm";
	names[2] = "box3.ppm";
	names[3] = "box4.ppm";
	names[4] = "box5.ppm";
	names[5] = "box6.ppm";

	m_skybox = new Skybox(2048, names, m_cam);
    
	glMatrixMode(GL_MODELVIEW);
	//glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	// Setup two light sources
	float light0_position[4];
	float light0_ambient[4];
	float light0_diffuse[4];

	float light1_position[4];
	float light1_ambient[4];
	float light1_diffuse[4];

	light0_position[0] =   1.0f; light0_ambient[0] = 0.8f; light0_diffuse[0] = 0.8f;
	light0_position[1] =   1.0f; light0_ambient[1] = 0.8f; light0_diffuse[1] = 0.8f;
	light0_position[2] =   0.0f; light0_ambient[2] = 0.8f; light0_diffuse[2] = 0.8f;
	light0_position[3] =   1.0f; light0_ambient[3] = 0.1f; light0_diffuse[3] = 1.0f;

	light1_position[0] =   0.0f; light1_ambient[0] = 0.1f; light1_diffuse[0] = 0.5f;
	light1_position[1] =  -1.0f; light1_ambient[1] = 0.1f; light1_diffuse[1] = 0.5f;
	light1_position[2] =   0.0f; light1_ambient[2] = 0.1f; light1_diffuse[2] = 0.5f;
	light1_position[3] =   1.0f; light1_ambient[3] = 1.0f; light1_diffuse[3] = 1.0f;

	// Light 1
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT0);

	// Light 2
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHT1);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Enable z buffer and gouroud shading
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glDepthFunc(GL_LESS);
	glShadeModel (GL_SMOOTH);
	
	
}
 
void RenderFrame::resizeGL(int w, int h)
{    
	if(h == 0)
	{
		h = 1;
	}

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100000);
	glMatrixMode(GL_MODELVIEW);

}
void RenderFrame::setCam() 
{
    if(Game::getFighter()) 
    {
        glVector<float> pos = (*(static_cast<Transformable*>(Game::getFighter()))).getPosition();
        glVector<float> front=(*(static_cast<Transformable*>(Game::getFighter()))).getFront();
        glVector<float> up = (*(static_cast<Transformable*>(Game::getFighter()))).getUp();
        glVector<float> side =(*(static_cast<Transformable*>(Game::getFighter()))).getSide();
        m_cam.setLocation(pos, front, up, side);
    }
}
void RenderFrame::paintGL()
{   
    if(reload > 15)
    {
        shoot = true;
        reload = 0;
    }
    reload++;
    
    //Steuerung updaten
    //if(steuerung)
    //{
        if(joystick) {
            joys->update();
        }
        Keyboard::update();
    //}
    //Emitter
    //Game::getEmitterFlug()->createPartikel();
    //Game::getEmitterFlug()->update();

    setCam();
    setFocus();
	// Set black background color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Clear bg color and enable depth test (z-Buffer)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render objects
	if(m_skybox)
	{
	    m_skybox->render();
	}

	if(Game::getFighter())
	{
		Game::getFighter()->render(!Game::getHud()->getView());
	}
	if(Game::getGalaxis()) 
	{
		Game::getGalaxis()->render();
	}
    
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glLoadIdentity();
        QPainter painter(this);
		Game::getHud()->setPainter( &painter );
        if(Game::getFighter()) {
			
        	Game::getHud()->setLevel(Game::getGalaxis()->getLevelnumber());
            	Game::getHud()->setIncLevel(Game::getGalaxis()->shouldIncLevel());
   	        Game::getHud()->setFighterData(Game::getFighter()->getDamage(), Game::getScore(), 			Game::getFighter()->getSpeed());
   	        Game::getHud()->setAstroidsVector(Game::getCollision()->getCollisionVector());
            	Game::getHud()->draw(width(),height(),font());
            if(Game::getCollision()->getWarning())
            {
                if(!warning_sound)
                {
            	   SoundManager::playWarningSound();
            	   warning_sound = true;
            	}
                Game::getHud()->drawWarning();
                
            }else
            {
                warning_sound = false;
            	SoundManager::stopWarningSound();
            }  
        }
        if(Game::getFighter()->getDamage()>=100)
        {
			Game::getFighter()->resetDamage();
        	menu = true;
        }
        if(menu)
        {
            Menu::drawSplash(width(),height(), Game::getHud());
            if(paintHighscore)
            {
            	Game::getHud()->drawHighscore();
            }
        }
        painter.end();
        glPopMatrix();
        glPopAttrib();
        glMatrixMode(GL_MODELVIEW);   

    glFinish();
	// Call back buffer
	swapBuffers();
}

void RenderFrame::keyPressEvent (QKeyEvent  *event)
{
    Keyboard::keypressed(event);

    if(menu) {
        if (event->key() == Qt::Key_Return)
        {   
            start();
            SoundManager::playBattleMusic();
        }
      
    }
    if (event->key() == Qt::Key_H)
    {
        		paintHighscore = !paintHighscore;
        		cout<<"HALLLO!!!!!!!!!!!!!!";
    }
    
    
}

void RenderFrame::keyReleaseEvent (QKeyEvent  *event)
{  
    Keyboard::keyrelease(event);
}

void RenderFrame::setupViewport(int width, int height)
{
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);
}
