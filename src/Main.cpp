#include "view/MainWindow.hpp"

using namespace std;

#include "io/Read3DS.hpp"
#include "rendering/TexturedMesh.hpp"
#include "rendering/Bullet.hpp"
#include "rendering/Fighter.hpp"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
     MainWindow mainWindow;
     mainWindow.show();
 
     return app.exec();


    
}
