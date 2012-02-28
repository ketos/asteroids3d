#include "MainWindow.hpp"

#include "io/TriangleMeshFactory.hpp"
#include "io/Read3DS.hpp"
#include "rendering/TexturedMesh.hpp"

#include <QtGui>

using std::cout;
using std::endl;

MainWindow::MainWindow(QMainWindow *parent)
{
	// Set window title an size
    setWindowTitle("Asteroids3D");
    resize(800, 600);

    // Create a new render frame and set as central widget.
    // If we don't want to use a full screen widget, we would
    // need to setup a proper parent (i.e. Frame object) here.
    m_renderFrame = new RenderFrame();
    setCentralWidget(m_renderFrame);
}

MainWindow::~MainWindow()
{
	// Free resources (just the render frame).
	delete m_renderFrame;
}
