#include "application/gui/MainScreen.hpp"

namespace application::gui
{
    MainScreen::MainScreen()
        : led1(screen, red)
        , led2(screen, blue)
        , led3(screen, green)
        , labelLed1(screen, infra::BoundedConstString("Led1\0"))
        , labelLed2(screen, infra::BoundedConstString("Led2\0"))
        , labelLed3(screen, infra::BoundedConstString("Led3\0"))
        , button1(screen)
        , button2(screen)
        , button3(screen)
        , labelButton1(screen, infra::BoundedConstString("Button1\0"))
        , labelButton2(screen, infra::BoundedConstString("Button2\0"))
        , labelButton3(screen, infra::BoundedConstString("Button3\0"))
    {}
}
