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
#include "io/SoundManager.hpp"
#include "io/joystick.h"

Camera RenderFrame::m_cam;
float RenderFrame::f_speed = 100;
float RenderFrame::f_angle = 0.05;
float RenderFrame::deadzone=12500;   


RenderFrame::RenderFrame(QWidget* parent) : QGLWidget(parent)
{
    
    // set up animation timer
    m_timer = new QTimer();
    m_timer->setInterval(25);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()),Qt::QueuedConnection);
    
    joys = new Joystick();
    
    joyConnect();    

	setAutoFillBackground(false);
	m_mesh  = 0;
	galaxis = 0;
    i = 0;
    loadModel("bearcat.3ds");
    show();
    SoundManager::playBackground();
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
    delete m_mesh;
    delete m_skybox;
    SoundManager::deleteManager();
}

void RenderFrame::loadModel(string filename)
{

	// Delete currently present model if necessary
	if(m_mesh == 0)
	{
		delete m_mesh;
	}

	// Load new model
	m_mesh = new Fighter;
	Read3DS reader(filename.c_str());
	reader.getMesh(*(static_cast<TexturedMesh*>(m_mesh)));

	// load the glaxis width all planets 
	galaxis = new Galaxis();


    // // start collision thread
    //    if (m_coll != 0)
    //            {
    //                    if (m_coll->isRunning())
    //                    {
    //                            //Thread vorhanden und Läuft
    //                            m_coll->stop();
    //                    }
    //                    delete m_coll;
    //            }
    m_coll = new Collision( (static_cast<Fighter*>(m_mesh)), galaxis);
    m_coll->start();
    
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
	
	hins = new HUD();
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

	// Set 'LookAt'
    //m_cam.apply();
    /*if(i==0) {
        m_cam.apply();
        i++;
    } else {
        setCam();
    }*/
}
void RenderFrame::setCam() {

    glVector<float> pos = (*(static_cast<Transformable*>(m_mesh))).getPosition();
    glVector<float> front=(*(static_cast<Transformable*>(m_mesh))).getFront();
    glVector<float> up = (*(static_cast<Transformable*>(m_mesh))).getUp();
    //Quaternion<float> quat = (*(static_cast<Transformable*>(m_mesh))).getRotation();
    //std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    //std::cout << lookat.x << " " << lookat.y << " " << lookat.z << std::endl;
    m_cam.setLocation(pos, front, up);

}
void RenderFrame::paintGL()
{    
    if(joystick) {
        control();
    }
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

	if(m_mesh)
	{
		m_mesh->render();
	}
	if(galaxis)
	{
		galaxis->render();
	}

    
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glLoadIdentity();
        QPainter painter(this);
        //painter.setRenderHint(QPainter::Antialiasing);
		hins->setAstroidsVector(m_coll->getCollisionVector());
		//std::cout<<"Ich habe die Liste"<<std::endl;
        hins->draw(&painter,width(),height(),font());
     	//std::cout<<"und hab gezichnet"<<std::endl;
        painter.end();
        // glPopMatrix();
        // glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();
        glMatrixMode(GL_MODELVIEW);
    
        glFinish();
	    // Call back buffer
	    swapBuffers();
}

void RenderFrame::keyPressEvent (QKeyEvent  *event)
{
	// State of key is pressed
	m_pressedKeys.insert(event->key());
	paintGL();
}

void RenderFrame::keyReleaseEvent (QKeyEvent  *event)
{  
	// State of key is unpressed
	m_pressedKeys.erase(event->key());
	paintGL();
} 

void RenderFrame::moveCurrentMesh()
{

    if(m_mesh)
    {
    	// Controller for moving and rotation
    	if (m_pressedKeys.find(Qt::Key_W) != m_pressedKeys.end())
    	{
            //m_mesh->move(STRAFE, -f_speed);
            (static_cast<Fighter*>(m_mesh))->changeSpeed(10);
    	}

    	if (m_pressedKeys.find(Qt::Key_S) != m_pressedKeys.end())
    	{
            //m_mesh->move(STRAFE, f_speed);
            (static_cast<Fighter*>(m_mesh))->changeSpeed(-10);
    	}

    	if (m_pressedKeys.find(Qt::Key_Up) != m_pressedKeys.end())
    	{
            m_mesh->rotate(PITCH, f_angle);
    	}

    	if (m_pressedKeys.find(Qt::Key_Down) != m_pressedKeys.end())
    	{
            m_mesh->rotate(PITCH, -f_angle);
    	}

    	if (m_pressedKeys.find(Qt::Key_Left) != m_pressedKeys.end())
    	{
            m_mesh->rotate(YAW,  f_angle);
    	}

    	if (m_pressedKeys.find(Qt::Key_Right) != m_pressedKeys.end())
    	{
            m_mesh->rotate(YAW, -f_angle);
    	}
    	// Schießen !!
    	if (m_pressedKeys.find(Qt::Key_Space) != m_pressedKeys.end())
    	{
    		(static_cast<Fighter*>(m_mesh))->shoot();
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
    }
}

void RenderFrame::control() {
    if(joys->getAxis(0) <-deadzone) {
        m_mesh->rotate(YAW,  f_angle);
    }
    if(joys->getAxis(0) > deadzone) {
        m_mesh->rotate(YAW,  -f_angle);
    }
    if(joys->getAxis(1) <-deadzone) {
        m_mesh->rotate(PITCH,  f_angle);
    }
    if(joys->getAxis(1) > deadzone) {
        m_mesh->rotate(PITCH,  -f_angle);
    }
    if(joys->getAxis(2) > deadzone) {
        (static_cast<Fighter*>(m_mesh))->changeSpeed(10);
    }
    if(joys->getAxis(5) > deadzone) {
        (static_cast<Fighter*>(m_mesh))->changeSpeed(-10);
    }
    if(joys->getAxis(4) <-2*deadzone) {
        m_cam.zoom(-15);
    }
    if(joys->getAxis(4) > 2*deadzone) {
        m_cam.zoom(15);
    }
    if(joys->getButton(0) > 0) { //A
        (static_cast<Fighter*>(m_mesh))->shoot();
    }/*
    if(joys->getButton(1) > 0) { //B
    }
    if(joys->getButton(2) > 0) { //X
    }
    if(joys->getButton(3) > 0) { //Y
    }*/
    if(joys->getButton(4) > 0) { //LB
        m_cam.changeheight(5);
    }
    if(joys->getButton(5) > 0) { //RB
        m_cam.changeheight(-5);
    }
    if(joys->getButton(6) > 0) { //Back
        loadModel("arrow.3ds");    
    }
    if(joys->getButton(7) > 0) { //Start
        loadModel("bearcat.3ds");    
    }/*
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
    }*/
}

void RenderFrame::setupViewport(int width, int height)
{
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);
}

HUD* RenderFrame::getHUD()
{
    return hins;
}

