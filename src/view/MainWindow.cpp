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
    setWindowTitle("3D-Viewer");
    resize(800, 600);

    // Create a new render frame and set as central widget.
    // If we don't want to use a full screen widget, we would
    // need to setup a proper parent (i.e. Frame object) here.
    m_renderFrame = new RenderFrame();
    setCentralWidget(m_renderFrame);
    
    // Create a file menu and add action. For larger projects
    // it would we more comfortable to use the QTDesigner tool
    // to create the GUI code for us
    m_fileMenu = menuBar()->addMenu("File");
    QAction* openAction = m_fileMenu->addAction("Open...");
    QAction* quitAction = m_fileMenu->addAction("Quit...");
    
    // Connect the activation signals of the created actions
    // with the proper slots.
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

}

MainWindow::~MainWindow()
{
	// Free resources (just the render frame).
	delete m_renderFrame;
}

void MainWindow::openFile()
{
	m_renderFrame->m_timer->stop();
	// Display a model file selection dialog
    QString filename = QFileDialog::getOpenFileName(this, "Load mesh", "",  "3DS Models (*.3ds)");

    // Load selected model into render frame
    m_renderFrame->loadModel(filename.toStdString());

}





