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
#include "io/joystick.h"
#include "io/SoundManager.hpp"

#include <string>

#include "view/Menu.hpp"


Camera RenderFrame::m_cam;
float RenderFrame::f_speed = 100;
float RenderFrame::f_angle = 0.025;
float RenderFrame::deadzone = 7000;
float RenderFrame::maxjoy = 32000;
float RenderFrame::shootTime = 750;
bool menu = false; 
bool warning_sound = false;

RenderFrame::RenderFrame(QWidget* parent) : QGLWidget(parent)
{
    
    // set up animation timer
    m_timer = new QTimer();
    m_timer->setInterval(25);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()),Qt::QueuedConnection);
    
    m_timer2=new QTimer();
    m_timer2->setInterval(shootTime);
    connect(m_timer2, SIGNAL(timeout()), this, SLOT(updateShoot()));
    m_timer2->start(); 
    
    shoot = true;
    
    joys = new Joystick();
    
    joyConnect();    

	setAutoFillBackground(false);

    show();
    menu = true;
}

void RenderFrame::joyConnect() {
    if(joys->init("/dev/input/js0") > -1) {
        std::cout << "connected" << std::endl;
        joystick = true;
    } else {             
        std::cout << "no joystick" << std::endl;
        joystick = false;
    }
}

RenderFrame::~RenderFrame()
{
    if(joystick) {
        joys->stop();
    }
    //delete joysticks;
    //delete keyboard;
    delete Game::getFighter();
    delete m_skybox;
    SoundManager::deleteManager();
}

void RenderFrame::start()
{
    menu = false;
    Menu::deleteSplash();
    
    Game::Init();

	std::string filenamer = "res/config/config.xml";
	Game::getGalaxis()->addLevel( filenamer );	

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
    if(joystick) {
        control();
    }

    Game::getEmitterFlug()->createPartikel();
    Game::getEmitterFlug()->update();
    //if(Game::getFighter()) {
    //    if(joysticks->connected()) {
    //        joysticks->update();
    //    }
    //    keyboard->update();
    //}
    setCam();
    setFocus();
	moveCurrentMesh();
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
   	        Game::getHud()->setFighterData(Game::getFighter()->getDamage(), Game::getScore(), Game::getFighter()->getSpeed());
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
        if(menu) {
            Menu::drawSplash(width(),height(), Game::getHud());
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
    //keyboard->keypressed(event);
	// State of key is pressed
	m_pressedKeys.insert(event->key());

    if(menu) {
        if (m_pressedKeys.find(Qt::Key_Return) != m_pressedKeys.end())
        {   
            start();
            SoundManager::playBattleMusic();
        }
    }
}

void RenderFrame::keyReleaseEvent (QKeyEvent  *event)
{  
    //keyboard->keyrelease(event);
	// State of key is unpressed
	m_pressedKeys.erase(event->key());
} 

void RenderFrame::moveCurrentMesh()
{    
    if(Game::getFighter())
    {
    	// Controller for moving and rotation
    	if (m_pressedKeys.find(Qt::Key_W) != m_pressedKeys.end())
    	{
            //Game::getFighter()->move(STRAFE, -f_speed);
            (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(1);
    	}

    	if (m_pressedKeys.find(Qt::Key_S) != m_pressedKeys.end())
    	{
            //Game::getFighter()->move(STRAFE, f_speed);
            (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(-1);
    	}

    	if (m_pressedKeys.find(Qt::Key_Up) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(PITCH, f_angle);
    	}

    	if (m_pressedKeys.find(Qt::Key_Down) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(PITCH, -f_angle);
    	}

    	if (m_pressedKeys.find(Qt::Key_Left) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(YAW,  f_angle);
            Game::getFighter()->rotate(ROLL ,f_angle);
    	}

    	if (m_pressedKeys.find(Qt::Key_Right) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(YAW, -f_angle);
            Game::getFighter()->rotate(ROLL ,-f_angle);
    	}
    	// Schießen !!
    	if (m_pressedKeys.find(Qt::Key_Space) != m_pressedKeys.end())
    	{
            if(shoot) {
    		    (static_cast<Fighter*>(Game::getFighter()))->shoot();
                shoot = false;
                m_timer2->start();
            }
      	}
        // Ändern der Kamera
        if (m_pressedKeys.find(Qt::Key_PageUp) != m_pressedKeys.end())
        {
            m_cam.zoom(-15);
        }
        if (m_pressedKeys.find(Qt::Key_PageDown) != m_pressedKeys.end())
        {
            m_cam.zoom(15);
        } 
        if (m_pressedKeys.find(Qt::Key_9) != m_pressedKeys.end())
        {
            m_cam.changeheight(5);
        }    
        if (m_pressedKeys.find(Qt::Key_0) != m_pressedKeys.end())
        {
            m_cam.changeheight(-5);
        }
        //nicht löschen
        if (m_pressedKeys.find(Qt::Key_1) != m_pressedKeys.end())
        {
            m_cam.setEgo();
            //Cockpit löschen
            if (Game::getHud())
            {
            	Game::getHud()->deleteCockpit();	
            }
        }
        if (m_pressedKeys.find(Qt::Key_2) != m_pressedKeys.end())   
        {
            m_cam.setThird();
            //Cockpit löschen
            if (Game::getHud())
            {
            	Game::getHud()->deleteCockpit();	
            }
        }
        if (m_pressedKeys.find(Qt::Key_3) != m_pressedKeys.end())   
        {
       		
            m_cam.setThird();
            //Cockpit setzen
			if (Game::getHud())
            {
            	Game::getHud()->loadCockpit();	
            }
        }
    }
}

void RenderFrame::control() {
    if(Game::getFighter()) {
    if(joys->getAxis(0) <-deadzone || joys->getAxis(0) > deadzone ) { // joystick links links-rechts
        float angle = joys->getAxis(0) / maxjoy * f_angle;        
        Game::getFighter()->rotate(YAW,  -angle);
        Game::getFighter()->rotate(ROLL, -angle);
    }
    if(joys->getAxis(1) <-deadzone || joys->getAxis(1) > deadzone ) { // joystick links up-down
        float angle = joys->getAxis(1) / maxjoy * f_angle;
        Game::getFighter()->rotate(PITCH,  angle);
    }
    if(joys->getAxis(2) > deadzone) { // schulter links
        (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(1);
    }
    if(joys->getAxis(5) > deadzone) { // schulter rechts
        (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(-1);
    }
    if(joys->getAxis(4) <-4*deadzone) { // joystick rechts up-down
        m_cam.zoom(-15);
    }
    if(joys->getAxis(4) > 4*deadzone) {
        m_cam.zoom(15);
    }
    if(joys->getAxis(3) <-4*deadzone) { // joystick rechts links-rechts
        m_cam.changeside(-15);
    }
    if(joys->getAxis(3) > 4*deadzone) {
        m_cam.changeside(15);
    }
    if(joys->getButton(0) > 0) { //A
        if(shoot) {
            (static_cast<Fighter*>(Game::getFighter()))->shoot();
            shoot = false;
            m_timer2->start();
        }
    }
    if(joys->getButton(1) > 0) { //B
    }
    if(joys->getButton(2) > 0) { //X
        m_cam.setEgo();
    }
    if(joys->getButton(3) > 0) { //Y
        m_cam.setThird();
    }
    if(joys->getButton(4) > 0) { //LB
        m_cam.changeheight(5);
    }
    if(joys->getButton(5) > 0) { //RB
        m_cam.changeheight(-5);
    }
    if(joys->getButton(6) > 0) { //Back
        /*if(shoot) {
            shoot = false;
            loadModel("res/models/arrow.3ds");
            m_timer2->start();
        } */ 
    }
    if(joys->getButton(7) > 0) { //Start
        /*if(shoot) {
            shoot = false;
            loadModel("res/models/bearcat.3ds");
            m_timer2->start();
        } */   
    }
    if(joys->getButton(8) > 0) { //BIG
    }
    if(joys->getButton(9) > 0) { //AxisLeft
    }
    if(joys->getButton(10) > 0) {//AxisRight
    }
    if(joys->getButton(11) > 0) {//DpadRight
    }
    if(joys->getButton(12) > 0) {//DpadUp
    }
    if(joys->getButton(13) > 0) {//DpadLeft
    }
    if(joys->getButton(14) > 0) {//DpadDown
    }
    if(joys->getButton(15) > 0) {//None
    }
    }
}

void RenderFrame::updateShoot(){
    shoot = true;
    m_timer2->stop();
}

void RenderFrame::setupViewport(int width, int height)
{
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);
}
