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
#include "Galaxis.hpp"
#include "math/Collision.hpp"

#include "view/HUD.hpp"
#include <QGLWidget>
#include <QTimer>

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
   
   //void sound();
   
   QTimer* m_timer;

	/// The camera object tot display the scene
	static Camera m_cam;

   /**
    * @brief returns the HUD
    * @return the HUD
    */
   HUD* getHUD();

protected:

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
	 * @brief	Our custom mouse event handler
	 *
	 * @param	e	The generated mouse event description
	 */
	//void mouseMoveEvent(QMouseEvent* e);
	
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
	 * @brief   Moves the camera in the x-y plane if dx and / or dy are > MOUSE_SENSITY
	 *
	 * @param 	dx 	The number of pixels the mouse has moved in x direction
	 * @param	dy 	The number of pixels the mouse has moved in y direction
	 */
	//void moveCamXY(int dx, int dy);

	/**
	 * @brief   Moves the camera in the z-x plane dy is > MOUSE_SENSITY
	 *
	 * @param 	dx 	The number of pixels the mouse has moved in x direction
	 * @param	dy 	The number of pixels the mouse has moved in y direction

	 */
	//void moveCamZ(int dy);

	/**
	 * @brief   Turns the camera around the current up-axis if
	 * 			dx and / or dy are > MOUSE_SENSITY
	 *
	 * @param 	dx 	The number of pixels the mouse has moved in x direction
	 * @param	dy 	The number of pixels the mouse has moved in y direction
	 */
	//void moveCamHead(int dx, int dy);

	/**
	 * @brief The currently loaded triangle mesh
	 */
	TriangleMesh*	m_mesh;
	
	/**
	 * @brief the collision thread
	 */
        Collision* m_coll;

	/**
	 * @brief the current loaded Galaxis
	 */
	Galaxis* galaxis;
	/**
	 * @brief A skybox for the scene
	 */
	Skybox* m_skybox;

	/**
	 * @brief The last x position of the mouse
	 */
	//int	m_mouseX;

	/**
	 * @brief The last y position of the mouse
	 */
	//int	m_mouseY;

	HUD* hins;

    static float f_speed;
    static float f_angle;
    
    int i;
    
    bool joyflag;
};

#endif // RENDER_FRAME_H
