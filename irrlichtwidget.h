/*
 * Irrlicht widget for Qt
 * Version 1.0
 */

#ifndef IRRLICHTWIDGET_HPP
#define IRRLICHTWIDGET_HPP

#if __cplusplus < 201103L && (!defined(_MSC_VER) || _MSC_VER < 1900)
#error This library needs C++11 to work.
#endif
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <functional>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#endif
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <irrlicht.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

class IrrlichtWidget : public QWidget{
    Q_OBJECT

public:
    IrrlichtWidget(irr::u32 width = 600, irr::u32 height = 400, irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()): QWidget(parent, f){
        setFixedSize(width, height);

        irr::SIrrlichtCreationParameters params;
        params.DriverType = driverType;
        params.WindowId = (void*)winId();
        params.WindowSize.Width = width;
        params.WindowSize.Height = height;
        m_device = irr::createDeviceEx(params);

        setAttribute(Qt::WA_OpaquePaintEvent);

        m_timer.setInterval(16);
        QObject::connect(&m_timer, &QTimer::timeout, [this](){
            emit inIrrlichtEventLoop();
            m_device->run();
        });
        m_timer.start();
    }

    IrrlichtWidget(QSize size, irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()): IrrlichtWidget(size.width(), size.height(), driverType, parent, f){}
    IrrlichtWidget(irr::video::E_DRIVER_TYPE driverType, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()): IrrlichtWidget(600, 400, driverType, parent, f){}
    IrrlichtWidget(irr::u32 width, irr::u32 height, QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags()): IrrlichtWidget(width, height, irr::video::EDT_OPENGL, parent, f){}
    IrrlichtWidget(QSize size, QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags()): IrrlichtWidget(size.width(), size.height(), irr::video::EDT_OPENGL, parent, f){}
    IrrlichtWidget(QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags()): IrrlichtWidget(600, 400, irr::video::EDT_OPENGL, parent, f){}

    ~IrrlichtWidget(){
        m_device->drop();
    }

    bool paused() const{
        return m_timer.signalsBlocked();
    }

    irr::IrrlichtDevice *getIrrlichtDevice() const{
        return m_device;
    }

    static void showMessageBox(std::function<void(QMessageBox::StandardButton)> lambda, QWidget *parent, const QString &title, const QString &text, QMessageBox::Icon icon = QMessageBox::Information, QFlags<QMessageBox::StandardButton> buttons = QMessageBox::Ok){
        QMessageBox *messageBox = new QMessageBox(icon, title, text, buttons, parent);
        messageBox->open(nullptr, nullptr);
        QObject::connect(messageBox, &QMessageBox::finished, [messageBox, lambda](){
            if(messageBox->clickedButton() == messageBox->button(QMessageBox::Ok)){
                lambda(QMessageBox::Ok);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Open)){
                lambda(QMessageBox::Open);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Save)){
                lambda(QMessageBox::Save);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Cancel)){
                lambda(QMessageBox::Cancel);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Close)){
                lambda(QMessageBox::Close);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Discard)){
                lambda(QMessageBox::Discard);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Apply)){
                lambda(QMessageBox::Apply);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Reset)){
                lambda(QMessageBox::Reset);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::RestoreDefaults)){
                lambda(QMessageBox::RestoreDefaults);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Help)){
                lambda(QMessageBox::Help);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::SaveAll)){
                lambda(QMessageBox::SaveAll);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Yes)){
                lambda(QMessageBox::Yes);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::YesToAll)){
                lambda(QMessageBox::YesToAll);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::No)){
                lambda(QMessageBox::No);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::NoToAll)){
                lambda(QMessageBox::NoToAll);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Abort)){
                lambda(QMessageBox::Abort);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Retry)){
                lambda(QMessageBox::Retry);
            }
            else if(messageBox->clickedButton() == messageBox->button(QMessageBox::Ignore)){
                lambda(QMessageBox::Ignore);
            }
            else{
                lambda(QMessageBox::NoButton);
            }
        });
    }

    static void showMessageBox(QWidget *parent, const QString &title, const QString &text, QMessageBox::Icon icon = QMessageBox::Information, QFlags<QMessageBox::StandardButton> buttons = QMessageBox::Ok){
        QMessageBox *messageBox = new QMessageBox(icon, title, text, buttons, parent);
        messageBox->open(nullptr, nullptr);
    }

public slots:
    void setPaused(bool paused){
        m_timer.blockSignals(paused);
    }

    void pause(){
        setPaused(true);
    }

    void resume(){
        setPaused(false);
    }

signals:
    void inIrrlichtEventLoop();

protected:
    void keyPressEvent(QKeyEvent *event) override{
        irr::SEvent irrEvent;
        irrEvent.EventType = irr::EET_KEY_INPUT_EVENT;
        IrrlichtKey irrKey;
        irrKey.code = (irr::EKEY_CODE)(0);
        irrKey.ch = (wchar_t)(0);
        if((event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) || (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9)){
            irrKey.code = (irr::EKEY_CODE)event->key();
            irrKey.ch = (wchar_t)event->key();
        }
        else{
            switch(event->key()){
            case Qt::Key_Up:
                irrKey.code = irr::KEY_UP;
                break;

            case Qt::Key_Down:
                irrKey.code = irr::KEY_DOWN;
                break;

            case Qt::Key_Left:
                irrKey.code = irr::KEY_LEFT;
                break;

            case Qt::Key_Right:
                irrKey.code = irr::KEY_RIGHT;
                break;
            }
        }
        if(irrKey.code != 0){
            irrEvent.KeyInput.Key = irrKey.code;
            irrEvent.KeyInput.Control = ((event->modifiers() & Qt::ControlModifier) != 0);
            irrEvent.KeyInput.Shift = ((event->modifiers() & Qt::ShiftModifier) != 0);
            irrEvent.KeyInput.Char = irrKey.ch;
            irrEvent.KeyInput.PressedDown = true;

            m_device->postEventFromUser(irrEvent);
        }
        event->ignore();
    }

    void keyReleaseEvent(QKeyEvent *event) override{
        irr::SEvent irrEvent;
        irrEvent.EventType = irr::EET_KEY_INPUT_EVENT;
        IrrlichtKey irrKey;
        irrKey.code = (irr::EKEY_CODE)(0);
        irrKey.ch = (wchar_t)(0);
        if((event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) || (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9)){
            irrKey.code = (irr::EKEY_CODE)event->key();
            irrKey.ch = (wchar_t)event->key();
        }
        else{
            switch(event->key()){
            case Qt::Key_Up:
                irrKey.code = irr::KEY_UP;
                break;

            case Qt::Key_Down:
                irrKey.code = irr::KEY_DOWN;
                break;

            case Qt::Key_Left:
                irrKey.code = irr::KEY_LEFT;
                break;

            case Qt::Key_Right:
                irrKey.code = irr::KEY_RIGHT;
                break;
            }
        }
        if(irrKey.code != 0){
            irrEvent.KeyInput.Key = irrKey.code;
            irrEvent.KeyInput.Control = ((event->modifiers() & Qt::ControlModifier) != 0);
            irrEvent.KeyInput.Shift = ((event->modifiers() & Qt::ShiftModifier) != 0);
            irrEvent.KeyInput.Char = irrKey.ch;
            irrEvent.KeyInput.PressedDown = false;

            m_device->postEventFromUser(irrEvent);
        }
        event->ignore();
    }

    void mousePressEvent(QMouseEvent *event) override{
        irr::SEvent irrEvent;

        irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;

        switch(event->button()){
        case Qt::LeftButton:
            irrEvent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
            break;

        case Qt::MidButton:
            irrEvent.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
            break;

        case Qt::RightButton:
            irrEvent.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
            break;

        default:
            return;
        }

        irrEvent.MouseInput.X = event->x();
        irrEvent.MouseInput.Y = event->y();
        irrEvent.MouseInput.Wheel = 0.0f;

        m_device->postEventFromUser(irrEvent);
        event->ignore();
    }

    void mouseReleaseEvent(QMouseEvent* event) override{
        irr::SEvent irrEvent;

        irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;

        switch(event->button()){
        case Qt::LeftButton:
            irrEvent.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
            break;

        case Qt::MidButton:
            irrEvent.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
            break;

        case Qt::RightButton:
            irrEvent.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
            break;

        default:
            return;
        }

        irrEvent.MouseInput.X = event->x();
        irrEvent.MouseInput.Y = event->y();
        irrEvent.MouseInput.Wheel = 0.0f;

        m_device->postEventFromUser(irrEvent);
        event->ignore();
    }

    void wheelEvent(QWheelEvent* event) override{
        if(event->orientation() == Qt::Vertical){
            irr::SEvent irrEvent;

            irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;

            irrEvent.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
            irrEvent.MouseInput.X = 0;
            irrEvent.MouseInput.Y = 0;
            irrEvent.MouseInput.Wheel = event->delta() / 120.0f;

            m_device->postEventFromUser(irrEvent);
        }
        event->ignore();
    }


private:
    struct IrrlichtKey{
        irr::EKEY_CODE code;
        wchar_t ch;
    };

    irr::IrrlichtDevice *m_device;
    QTimer m_timer;
};

#endif // IRRLICHTWIDGET_HPP
