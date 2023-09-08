#include "application/parsers/Display.hpp"
#include "infra/util/Optional.hpp"

namespace application::parsers
{
    Display::Display(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithCommands& terminal, services::Tracer& tracer, hal::DisplayLcd& display, hal::OutputPin& backlight)
        : services::TerminalCommandsAndMenu(terminal)
        , menu(name, description, *this)
        , terminal(terminal)
        , tracer(tracer)
        , display(display)
        , backlight(backlight)
    {}

    infra::MemoryRange<const services::TerminalCommands::Command> Display::Commands()
    {
        static const std::array<Command, 4> commands = { { { { "d", "dim", "Show display dimensions [width, height] pixels" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                                                               {
                                                                   this->GetDimensions(params);
                                                               } },
            { { "bl", "backlight", "Backlight [on|off]" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->Backlight(params);
                } },
            { { "p", "pixel", "Draw pixel" }, [this]([[maybe_unused]] const infra::BoundedConstString& params) {

             } },
            { { "b", "background", "Draw background [white|black|red|green|blue]" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->DrawBackground(params);
                } } } };

        return infra::MakeRange(commands);
    }

    services::TerminalCommandsAndMenu::MenuInfo& Display::Menu()
    {
        return menu;
    }

    void Display::GetDimensions(const infra::BoundedConstString& params)
    {
        tracer.Trace() << "Display LCD dimensions: [" << display.Width() << ", " << display.Height() << "]\r\n";
    }

    void Display::DrawBackground(const infra::BoundedConstString& params)
    {
        infra::Optional<hal::Color> color;

        if (params == "white")
            color.Emplace(0xff, 0xff, 0xff);
        else if (params == "black")
            color.Emplace(0x00, 0x00, 0x00);
        else if (params == "red")
            color.Emplace(0xff, 0x00, 0x00);
        else if (params == "green")
            color.Emplace(0x00, 0xff, 0x00);
        else if (params == "blue")
            color.Emplace(0x00, 0x00, 0xff);
        else
        {
            tracer.Trace() << "Invalid color!\r\n";
            return;
        }

        tracer.Trace() << "Drawing background...\r\n";
        display.DrawBackground(*color, [this]()
            {
                tracer.Trace() << "Done\r\n";
            });
    }

    void Display::Backlight(const infra::BoundedConstString& params)
    {
        backlight.Set(params == "on");
    }
}
