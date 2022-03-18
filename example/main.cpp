/*
 * Irrlicht widget for Qt Example
 * Version 1.0
 * This example does the same thing as Irrlicht's Hello World example, but using Qt.
 * For detailed explanations of what the Irrlicht commands do, see Irrlicht's Hello World example.
 */

#include <QApplication>
#include <irrlicht.h>
#include "irrlichtwidget.hpp"

//Don't forget to change the Irrlicht path to the one you have, otherwise it won't work. You also need to change this in the .pro file.
#define IRRLICHTPATH "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\Libraries\\irrlicht-1.8.4"

//Also, if you're on Windows, don't forget to copy Irrlicht.dll to the build directory.

int main(int argc, char **argv){
    QApplication app(argc, argv);

    IrrlichtWidget irrlichtWidget(640, 480, irr::video::EDT_OPENGL);    //Create an Irrlicht widget with dimensions 640x480 and with an OpenGL driver.
    irr::IrrlichtDevice *device = irrlichtWidget.getIrrlichtDevice();   //Get the Irrlicht device. Equivalent to irr::createDevice() in plain Irrlicht.
    irr::scene::ISceneManager *sceneManager = device->getSceneManager();
    irr::video::IVideoDriver *driver = device->getVideoDriver();

    irrlichtWidget.setWindowTitle("Hello World! - Irrlicht Widget Demo");

    irr::scene::IAnimatedMesh *mesh = sceneManager->getMesh(IRRLICHTPATH"/media/sydney.md2");
    if(mesh == nullptr){
        return 1;
    }
    irr::scene::IAnimatedMeshSceneNode *node = sceneManager->addAnimatedMeshSceneNode(mesh);

    if(node != nullptr){
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMD2Animation(irr::scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture(IRRLICHTPATH"/media/sydney.bmp"));
    }

    sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 30, -40), irr::core::vector3df(0, 5, 0));

    QObject::connect(&irrlichtWidget, &IrrlichtWidget::inIrrlichtEventLoop, [=](){   //Equivalent to while(device->run()) in plain Irrlicht.
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        sceneManager->drawAll();

        driver->endScene();

        //device->run() isn't needed, it's called internally in the Irrlicht widget.
    });

    irrlichtWidget.show();

    //device->drop() isn't needed, it's called internally in the Irrlicht widget's desctuctor.

    return app.exec();
}
