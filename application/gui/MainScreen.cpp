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
        , labelButton1(button1, infra::BoundedConstString("Button1\0"))
        , labelButton2(button2, infra::BoundedConstString("Button2\0"))
        , labelButton3(button3, infra::BoundedConstString("Button3\0"))
    {
        led1.Align(embedded::lvgl::core::Position::Alignment::topMiddle, -120, 0);
        led2.Align(embedded::lvgl::core::Position::Alignment::topMiddle, 0, 0);
        led3.Align(embedded::lvgl::core::Position::Alignment::topMiddle, 120, 0);

        button1.Align(embedded::lvgl::core::Position::Alignment::center, -120, 0);
        button2.Align(embedded::lvgl::core::Position::Alignment::center, 0, 0);
        button3.Align(embedded::lvgl::core::Position::Alignment::center, 120, 0);

        labelLed1.AlignTo(led1, embedded::lvgl::core::Position::Alignment::center, 0, 25);
        labelLed2.AlignTo(led2, embedded::lvgl::core::Position::Alignment::center, 0, 25);
        labelLed3.AlignTo(led3, embedded::lvgl::core::Position::Alignment::center, 0, 25);

        labelButton1.Align(embedded::lvgl::core::Position::Alignment::center, 0, 0);
        labelButton2.Align(embedded::lvgl::core::Position::Alignment::center, 0, 0);
        labelButton3.Align(embedded::lvgl::core::Position::Alignment::center, 0, 0);
    }
}
