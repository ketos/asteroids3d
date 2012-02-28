/**
 *  @file  RenderFrame.hpp
 *
 *  @date  19.02.2012
 *  @author Thomas Wiemann
 */
#ifndef RENDER_FRAME_H
#define RENDER_FRAME_H


#include <set>
#include <QGLWidget>
#include <QTimer>
#include "view/Camera.hpp"
#include "rendering/TriangleMesh.hpp"
#include "rendering/Skybox.hpp"
#include "rendering/Asteorid.hpp"
#include "math/Global.hpp"
#include "io/joystick.h"
#include "control/keyboard.hpp"
#include "control/joystickcontrol.hpp"
#include "logic/Game.hpp"

class RenderFrame : public QGLWidget
{
    Q_OBJECT
 
public:

	/**
	 * @brief	Ctor.
	 */
    RenderFrame(QWidget *parent = 0);

    /**
     * @brief	Dtor.
     */
    ~RenderFrame();
	
    /**
     * @brief 	Loads the given file and creates a new model.
     * 			Is a model is already present, it is replaced
     * 			with the new one.
     */
    void loadModel(string modelName);
  
    /**
     *
     */
    void setupViewport(int width, int height);
   
    QTimer* m_timer;
    
    QTimer* m_timer2;
    
    Joystick *joys;
    
    //Keyboard* keyboard;
     
    //JoystickControl* joysticks;

	/// The camera object tot display the scene
    static Camera m_cam;

protected:
    
    void control();

    void setCam();
	
    /// The set of currently pressed keys
	std::set<int> m_pressedKeys;

	/**
	 * @brief	Our custom key press handler
	 *
	 * @param	e	The generated key event description
	 */
	void keyPressEvent(QKeyEvent* e);

	/**
	 * @brief	Our custom key release event handler
	 *
	 * @param	e	The generated key event description
	 */
	void keyReleaseEvent(QKeyEvent* e);
	
	/**
	 * @brief 	The OpenGL initialization method. This is always called before
	 * 			the fist paintGL operation, so all necessary OpenGL initialization
	 * 			should be done here
	 */
    void initializeGL();

    /**
     * @brief	The resize method for OpenGL related stuff
     */
    void resizeGL(int w, int h); 

    /**
     * @brief	The render function.
     */
    void paintGL();
   
    /**
     * @brief	Reads the current key states and applies the
     * 			needed transformations to the active triangle mesh
     */
	void moveCurrentMesh();
	/**
	 * @brief A skybox for the scene
	 */
	Skybox* m_skybox;

    static float f_speed;
    static float f_angle;
    static float deadzone;
    static float maxjoy;
    static float shootTime;
    
    bool joystick;
    
    bool shoot;

    void joyConnect();

private slots:
    void updateShoot();
};

#endif // RENDER_FRAME_H
