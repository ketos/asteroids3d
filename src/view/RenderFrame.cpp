#include "RenderFrame.hpp"

#include <set>

#include <QKeyEvent>
#include <QMouseEvent>

#include "rendering/TexturedMesh.hpp"
#include "io/Read3DS.hpp"

RenderFrame::RenderFrame(QWidget* parent) : QGLWidget(parent)
{
    // set up animation timer
//    m_timer = new QTimer();
//    m_timer->setInterval(25);
//    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()),Qt::QueuedConnection);
//    m_timer->start();
    
	m_mesh = 0;
	
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
	m_mesh = new TexturedMesh;
	Read3DS reader(filename.c_str());
	reader.getMesh(*(static_cast<TexturedMesh*>(m_mesh)));

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
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

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

	if(event->buttons() == Qt::MiddleButton)
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
