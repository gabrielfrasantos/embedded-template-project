#ifndef APPLICATION_PARSERS_GUI_HPP
#define APPLICATION_PARSERS_GUI_HPP

#include "implementations/lvgl/lvgl/interfaces/Controller.hpp"
#include "hal/interfaces/DisplayLcd.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "infra/util/BoundedString.hpp"
#include "infra/util/MemoryRange.hpp"
#include "services/tracer/TracerWithDateTime.hpp"
#include "services/util/Terminal.hpp"

namespace application::parsers
{
    class Gui
        : public services::TerminalCommandsAndMenu
    {
    public:
        Gui(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithMenu& terminal, services::Tracer& tracer, hal::DisplayLcd& display, hal::OutputPin& backlight);
        virtual ~Gui() = default;

        infra::MemoryRange<const services::TerminalCommands::Command> Commands() override;
        MenuInfo& Menu() override;

    private:
        void GetDimensions(const infra::BoundedConstString& params);
        void Backlight(const infra::BoundedConstString& params);
        void DrawBackground(const infra::BoundedConstString& params);

    private:
        class DisplayFacade
            : public embedded::lvgl::DriverDisplay
        {
        public:
            explicit DisplayFacade(hal::DisplayLcd& display);

            std::size_t GetHorizontalResolution() override;
            std::size_t GetVerticalResolution() override;

            infra::MemoryRange<embedded::lvgl::Color> GetBuffer1() override;
            infra::MemoryRange<embedded::lvgl::Color> GetBuffer2() override;
            std::size_t PixelSize() override;

            void Flush(embedded::lvgl::Area area, infra::MemoryRange<embedded::lvgl::Color> color, const infra::Function<void()>& onDone) override;

        private:
            constexpr static std::size_t maxWidth = 480;
            constexpr static std::size_t numberOfRows = 10;

            hal::DisplayLcd& display;
            infra::BoundedVector<embedded::lvgl::Color>::WithMaxSize<maxWidth * numberOfRows> buffer1;
        };

        class InputDeviceStub
            : public embedded::lvgl::DriverInputDevice
        {
        public:
            InputDeviceStub()
                : DriverInputDevice(DriverInputDevice::InputType::button)
            {}

            Response Read() override
            {
                return response;
            }

            void Feedback() override
            {}

        private:
            Response response;
        };

        MenuInfo menu;
        services::TerminalWithMenu& terminal;
        services::Tracer& tracer;
        hal::OutputPin& backlight;
        hal::DisplayLcd& display;
        DisplayFacade displayLvgl;
        InputDeviceStub inputDeviceLvgl;
        embedded::lvgl::Controller gui;
    };
}

#endif
