#ifndef APPLICATION_GUI_MAIN_SCREEN_HPP
#define APPLICATION_GUI_MAIN_SCREEN_HPP

#include "lvgl/core/Screen.hpp"
#include "lvgl/widgets/Button.hpp"
#include "lvgl/widgets/Led.hpp"
#include "lvgl/widgets/Label.hpp"

namespace application::gui
{
    class MainScreen
    {
    public:
        MainScreen();

    private:
        embedded::lvgl::core::Screen screen;
        hal::Color red{ hal::Color::Rgb::red };
        hal::Color blue{ hal::Color::Rgb::blue };
        hal::Color green{ hal::Color::Rgb::green };

        embedded::lvgl::widget::Led led1;
        embedded::lvgl::widget::Led led2;
        embedded::lvgl::widget::Led led3;
        embedded::lvgl::widget::Label labelLed1;
        embedded::lvgl::widget::Label labelLed2;
        embedded::lvgl::widget::Label labelLed3;
        embedded::lvgl::widget::Button button1;
        embedded::lvgl::widget::Button button2;
        embedded::lvgl::widget::Button button3;
        embedded::lvgl::widget::Label labelButton1;
        embedded::lvgl::widget::Label labelButton2;
        embedded::lvgl::widget::Label labelButton3;
    };
}

#endif
