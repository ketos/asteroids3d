#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__

/**
 *  @file  MainWindow.hpp
 *
 *  @date  19.02.2012
 *  @author Thomas Wiemann
 */


#include <QMainWindow>
#include <QMenuBar>
#include "RenderFrame.hpp"


/**
 * @brief   A simple main window class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

	/**
	 * @brief   Default constructor to create a main window
	 * 			with an initial size of 800 x 600 Pixels
	 */
	MainWindow(QMainWindow *parent = 0);

	/**
	 * @brief   Destructor.
	 */
	~MainWindow();
	
public slots:

	/**
	 * @brief	Display a QFileDialog to choose a model
	 * 			for the viewer
	 */
    void openFile();

private:

    /// Our custom QGLWidget class to display the scene
    RenderFrame* 	m_renderFrame;

	/// Our main menu for open and quit operations
	QMenu* 			m_fileMenu;
};

#endif
