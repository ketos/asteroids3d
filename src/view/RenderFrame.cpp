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


RenderFrame::RenderFrame(QWidget* parent) : QGLWidget(parent)
{
    // set up animation timer
   m_timer = new QTimer();
   m_timer->setInterval(25);
   connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()),Qt::QueuedConnection);
   m_timer->start();
	setAutoFillBackground(false);
	m_mesh  = 0;
	galaxis = 0;
	show();
}

RenderFrame::~RenderFrame()
{
    delete m_mesh;
    delete m_skybox;
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
	//Hier Aenderung!! --> m_mesh = new TexturedMesh;
	Read3DS reader(filename.c_str());
	reader.getMesh(*(static_cast<TexturedMesh*>(m_mesh)));
	std::cout << "Fighter erstellt und vor der Erstellung der Galaxy" << std::endl;
	// load the glaxis width all planets 
	galaxis = new Galaxis();
	//Vectors
	glVector<float> v1(m_cam.m_px, m_cam.m_py, m_cam.m_pz-1000);
	glVector<float> v2(0.0, 0.0, 0.0);
	Asteorid *a1 = new Asteorid(v2, v1);
	galaxis->addAsteorid(v1,v2);
	std::cout << "Galaxy erstellt und so" << std::endl;

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
	m_cam.apply();
}

void RenderFrame::paintGL()
{    
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
    // painter.setRenderHint(QPainter::Antialiasing);
     hins->draw(&painter,width(),height(),font());
     
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
    	if (m_pressedKeys.find(Qt::Key_Q) != m_pressedKeys.end())
    	{
    		m_mesh->rotate(ROLL, 0.1);
    	}

    	if (m_pressedKeys.find(Qt::Key_E) != m_pressedKeys.end())
    	{
    		m_mesh->rotate(ROLL, -0.1);
    	}

    	if (m_pressedKeys.find(Qt::Key_A) != m_pressedKeys.end())
    	{
    		m_mesh->rotate(YAW, 0.1);
    	}

    	if (m_pressedKeys.find(Qt::Key_D) != m_pressedKeys.end())
    	{
    		m_mesh->rotate(YAW, -0.1);
    	}

    	if (m_pressedKeys.find(Qt::Key_W) != m_pressedKeys.end())
    	{
    		m_mesh->rotate(PITCH, 0.1);
    	}

    	if (m_pressedKeys.find(Qt::Key_S) != m_pressedKeys.end())
    	{
    		m_mesh->rotate(PITCH, -0.1);
    	}

    	if (m_pressedKeys.find(Qt::Key_Up) != m_pressedKeys.end())
    	{
    		m_mesh->move(STRAFE, -10);
    	}

    	if (m_pressedKeys.find(Qt::Key_Down) != m_pressedKeys.end())
    	{
    		m_mesh->move(STRAFE, 10);
    	}

    	if (m_pressedKeys.find(Qt::Key_Left) != m_pressedKeys.end())
    	{
    		m_mesh->move(LIFT, 5);
    	}

    	if (m_pressedKeys.find(Qt::Key_Right) != m_pressedKeys.end())
    	{
    		m_mesh->move(LIFT, -5);
    	}

    	if (m_pressedKeys.find(Qt::Key_PageUp) != m_pressedKeys.end())
    	{
    		m_mesh->move(ACCEL, 5);
    	}

    	if (m_pressedKeys.find(Qt::Key_PageDown) != m_pressedKeys.end())
    	{
    		m_mesh->move(ACCEL, -5);
    	}
    	// Schießen !!
    	    	if (m_pressedKeys.find(Qt::Key_L) != m_pressedKeys.end())
    	{
    		(static_cast<Fighter*>(m_mesh))->shoot();
    	}
    }
}


void RenderFrame::mouseMoveEvent (QMouseEvent  *event)
{
	// Get number the number of pixel between the last
	// und current mouse position
	int dx = event->x() - m_mouseX;
	int dy = event->y() - m_mouseY;

	// Check which button was pressend and apply action
	if(event->buttons() == Qt::LeftButton)
	{
		moveCamXY(dx, dy);
	}

	if(event->buttons() == Qt::RightButton)
	{
		moveCamHead(dx, dy);
	}

	if(event->buttons() == Qt::MidButton)
	{
		moveCamZ(dy);
	}

	// Transform viewport
	m_cam.apply();

	// Save new coodinates
	m_mouseX = event->x();
	m_mouseY = event->y();

	paintGL();
}

void RenderFrame::moveCamXY(int dx, int dy)
{
	if(fabs(dx) > MOUSE_SENSITY)
	{
		if(dx > 0)
		{
			m_cam.turnRight();
		}

		else
		{
			m_cam.turnLeft();
		}

	}

	if(fabs(dy) > MOUSE_SENSITY)
	{
		if(dy > 0)
		{
			m_cam.moveBackward();
		}

		else
		{
			m_cam.moveForward();
		}
	}
}

void RenderFrame::moveCamZ(int dy)
{

	if(fabs(dy) > MOUSE_SENSITY)
	{
		if(dy > 0)
		{
			m_cam.moveUp();
		}

		else
		{
			m_cam.moveDown();
		}
	}
}

void RenderFrame::moveCamHead(int dx, int dy)
{

	if(fabs(dy) > MOUSE_SENSITY)
	{
		if(dy > 0)
		{
			m_cam.turnUp();
		}

		else
		{
			m_cam.turnDown();
		}
	}

	if(fabs(dx) > MOUSE_SENSITY)
	{
		if(dx > 0)
		{
			m_cam.turnRight();
		}

		else
		{
			m_cam.turnLeft();
		}
	}
}

void RenderFrame::setupViewport(int width, int height)
{
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);
}

