QT += widgets

#Change C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\Libraries\\irrlicht-1.8.4 to the path where you installed Irrlicht. You also need to change this in the main.cpp file.
INCLUDEPATH += "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\Libraries\\irrlicht-1.8.4\\include"
#Here you also need to change Win32-visualstudio if you're not compiling for Windows 32 bit using Visual Studio.
LIBS += -L"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\Libraries\\irrlicht-1.8.4\\lib\\Win32-visualstudio" -lIrrlicht

HEADERS += \
    irrlichtwidget.hpp

SOURCES += \
    main.cpp
