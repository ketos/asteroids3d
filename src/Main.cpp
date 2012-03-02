#include "view/MainWindow.hpp"

using namespace std;

//Aloha

#include "io/Read3DS.hpp"
#include "rendering/TexturedMesh.hpp"
#include "rendering/Bullet.hpp"
#include "rendering/Fighter.hpp"
#include <QApplication>
#include <QIcon>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("res/images/icon.png"));
    MainWindow mainWindow;
    mainWindow.show();
 
    return app.exec();
}
