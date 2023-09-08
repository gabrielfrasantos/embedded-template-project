#ifndef APPLICATION_PARSERS_DISPLAY_HPP
#define APPLICATION_PARSERS_DISPLAY_HPP

#include "hal/interfaces/DisplayLcd.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "services/tracer/TracerWithDateTime.hpp"
#include "services/util/Terminal.hpp"

namespace application::parsers
{
    class Display
        : public services::TerminalCommandsAndMenu
    {
    public:
        Display(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithCommands& terminal, services::Tracer& tracer, hal::DisplayLcd& display, hal::OutputPin& backlight);
        virtual ~Display() = default;

        infra::MemoryRange<const services::TerminalCommands::Command> Commands() override;
        MenuInfo& Menu() override;

    private:
        void GetDimensions(const infra::BoundedConstString& params);
        void Backlight(const infra::BoundedConstString& params);
        void DrawBackground(const infra::BoundedConstString& params);

        MenuInfo menu;
        services::TerminalWithCommands& terminal;
        services::Tracer& tracer;
        hal::DisplayLcd& display;
        hal::OutputPin& backlight;
    };
}

#endif
