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
     /*
    glVector<float> a (1.0f,2.0f,3.0f);
    glVector<float> b (2.0f,3.0f,4.0f);
    Bullet bullet (a,b);*/
    
}
