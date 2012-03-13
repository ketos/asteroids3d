/**
 *  @file  RenderFrame.hpp
 *
 *  @author gruppe3
 */
#ifndef RENDER_FRAME_H
#define RENDER_FRAME_H


#include <QInputDialog>
#include <set>
#include <QGLWidget>
#include <QTimer>
#include <QDir>
#include <QLabel>	
#include "io/ReadTXT.hpp"
#include "view/Camera.hpp"
#include "rendering/TriangleMesh.hpp"
#include "rendering/Skybox.hpp"
#include "rendering/Asteorid.hpp"
#include "math/Global.hpp"
#include "control/keyboard.hpp"
#ifdef LINUX
#include "control/joystickcontrol.hpp"
#endif
#include "logic/Game.hpp"
 
/**
 * @brief Starten und Render der Objekte
 */
class RenderFrame : public QGLWidget
{
    Q_OBJECT
 
public:

	/**
	 * @brief	Konstruktor
	 */
    RenderFrame(QWidget *parent = 0);

    /**
     * @brief	Destruktor
     */
    ~RenderFrame();
	
    /**
     * @brief  Initialisiert die Game, startet die Spielmusik und die Timer
     */
    void start();
  
    /**
     * @brief Initialisierung für den QPainter
     *
     * @param width Breite des Fensters
     * @param height Hoehe des Fensters
     */
    void setupViewport(int width, int height);

    /**
     * @brief QTimer für den ständigen Aufruf der PaintGL (alle 25ms)
     */
    QTimer* m_timer;
    
    /**
     * @brief QTimer für den Reload der Schüsse und die Trägheit der Bewegung
     */
    QTimer* m_timer2;

#ifdef LINUX	
    /**
     * @brief Joystick
     */
    JoystickControl* joys;
#endif
	
    /**
     * @brief Kamera
     */
    static Camera m_cam;

protected:
    /**
     * @brief updatet die Kameraposition zum Fighter
     */
    void setCam();

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
	 * @brief A skybox for the scene
	 */
	Skybox* m_skybox;
    
    /**
     * @brief gibt an ob ein Joystick angeschlossen ist oder nicht
     */
    bool joystick;
    
    /**
     * @brief gibt an ob der Highscore gezeichnet werden soll
     */
    bool paintHighscore;
    
    /**
     * @brief Label für die Eingabe des Usernamens
     */
    QLabel *textLabel;
    
private slots:
    /**
     * @brief wird alle 100ms vom Timer aufgerufen und leitet den Aufruf an die Game weiter
     */
    void Gameupdate();
    
private:
    /**
     * @brief String für den Username
     */
    QString userName;
    
    /**
     * @brief wird gesetzt, wenn man GameOver ist (wenn true wird der GameOver bildschirm angezeigt
     */
    bool gameOver;
};

#endif // RENDER_FRAME_H
