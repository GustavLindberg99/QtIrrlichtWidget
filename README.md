# Overview
The IrrlichtWidget class is a widget which allows you to use Irrlicht in Qt. It inherits from Qt's
QWidget class.

# Setup
This library requires Qt5, Irrlicht and C++11 or later to work. You can download Qt [here](https://www.qt.io/download-qt-installer?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) and Irrlicht [here](http://irrlicht.sourceforge.net/?page_id=10).

Start by downloading the file [irrlichtwidget.h](https://github.com/Gustav-Lindberg/QtIrrlichtWidget/blob/main/irrlichtwidget.h) and save it in the same folder as your project source code.

Download the file [irrlichtwidget.h](https://github.com/Gustav-Lindberg/QtIrrlichtWidget/blob/main/irrlichtwidget.h), save it to the folder containing your project source code, add it to your project and write `#include "irrlichtwidget.h"` in each file where you want to use the widget. You also need to add Irrlicht to your project, to do so in Qt Creator, add the following code to your .pro file, replacing `(IRRLICHTPATH)` with the path where you installed Irrlicht and `(YOUR OS)` with either Win64-visualstudio, Win32-visualstudio, Linux or MacOSX:

    INCLUDEPATH += "(IRRLICHTPATH)/include"
    LIBS += "(IRRLICHTPATH)/lib/(YOUR OS)" -lIrrlicht
    
Also, if you're using Windows, don't forget to copy Irrlicht.dll to the build directory. You can download Irrlicht.dll [here for 32-bit programs](https://github.com/Gustav-Lindberg/QtIrrlichtWidget/blob/main/Irrlicht.dll-Win32-VisualStudio/Irrlicht.dll?raw=true) and [here for 64-bit programs](https://github.com/Gustav-Lindberg/QtIrrlichtWidget/blob/main/Irrlicht.dll-Win64-VisualStudio/Irrlicht.dll?raw=true). These Irrlicht.dll files are the same as the ones made by Irrlicht.

# Usage
## Constructors of the `IrrlichtWidget` class
1. `IrrlichtWidget(irr::u32 width = 600, irr::u32 height = 400, irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())`

    Creates an Irrlicht widget with width `width`, height `height`, Irrlicht driver type `driverType`, parent widget `parent` and window flags `f`.
    
2. `IrrlichtWidget(QSize size, irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())`
    
    Same as constructor (1) but allows you to specify the widget size as a `QSize` instead of two integers.
    
3. `IrrlichtWidget(irr::video::E_DRIVER_TYPE driverType, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())`

    Same as constructor (1) with the width parameter equal to 600 and the height parameter equal to 400.
    
4. `IrrlichtWidget(irr::u32 width, irr::u32 height, QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags())`
    
    Same as contructor (1) with the driverType parameter equal to `irr::video::EDT_OPENGL`.
    
5. `IrrlichtWidget(QSize size, QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags())`

    Same as contructor (2) with the driverType parameter equal to `irr::video::EDT_OPENGL`.
    
6. `IrrlichtWidget(QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags())`

    Same as constructor (1) with the width parameter equal to 600, the height parameter equal to 400 and the driverType parameter equal to `irr::video::EDT_OPENGL`.
    
## Methods of the `IrrlichtWidget` class
* 260 methods inherited from `QWidget`. See http://doc.qt.io/qt-5/qwidget.html#public-functions.
* `bool paused() const`

    Returns `true` if the widget is paused and `false` otherwise. See also the slots `void setPaused(bool paused)`, `void pause()` and `void resume()`.
    
* `irr::IrrlichtDevice *getIrrlichtDevice() const`

    Returns the Irrlicht device associated to the widget.
    
## Slots of the `IrrlichtWidget` class
* 20 slots inherited from QWidget. See http://doc.qt.io/qt-5/qwidget.html#public-slots.
* `void setPaused(bool paused)`

    If `paused` is `true`, pauses the Irrlicht widget so that nothing moves in it. If `paused` is `false`, unpauses the Irrlicht widget.
    
* `void pause()`

    Same as `setPaused(true)`.
    
* `void resume()`

    Same as `setPaused(false)`.
    
## Signals of the `IrrlichtWidget` class
* 5 signals inherited from QWidget. See http://doc.qt.io/qt-5/qwidget.html#signals.
* `void inIrrlichtEventLoop()`

    This signal is emitted whenever the Irrlicht event loop should be run. The following code with the Irrlicht widget:
    
      QObject::connect(irrlichtWidget, &IrrlichtWidget::inIrrlichtEventLoop, [](){
          //whatever
      });
      
    is the same as the following code in plain Irrlicht:
    
      while(device->run()){
          //whatever
      }
      
    You don't have to call `device->run()` with the Irrlicht widget, it is already called internally.
    
## Static methods of the `IrrlichtWidget` class
* 16 static methods inerited from QWidget. See http://doc.qt.io/qt-5/qwidget.html#static-public-members.
* `static void showMessageBox(std::function<void(QMessageBox::StandardButton)> lambda, QWidget *parent, const QString &title, const QString &text, QMessageBox::Icon icon = QMessageBox::Information, QFlags<QMessageBox::StandardButton> buttons = QMessageBox::Ok)`
    
    Shows a message box with parent widget `parent`, window title `title`, message `text`, icon `icon` and buttons `buttons`, and runs `lambda` after the message box was closed. This static method is similar to `QMessageBox::information` etc, but the `QMessageBox` static methods make the Irrlicht widget become black while they are open.
    
* `static void showMessageBox(QWidget *parent, const QString &title, const QString &text, QMessageBox::Icon icon = QMessageBox::Information, QFlags<QMessageBox::StandardButton> buttons = QMessageBox::Ok)`

    Same as `showMessageBox([](){}, parent, title, text, icon, buttons)`.

# Example
You can download an example Qt project which uses the Irrlicht widget [here](https://github.com/Gustav-Lindberg/QtIrrlichtWidget/tree/main/example).
