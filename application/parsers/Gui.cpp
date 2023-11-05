#include "application/parsers/Gui.hpp"
#include "hal/interfaces/DisplayLcd.hpp"
#include "infra/util/MemoryRange.hpp"
#include "infra/util/ReallyAssert.hpp"

namespace application::parsers
{
    Gui::DisplayFacade::DisplayFacade(hal::DisplayLcd& display)
        : display(display)
    { }

    std::size_t Gui::DisplayFacade::GetHorizontalResolution()
    {
        return display.Width();
    }

    std::size_t Gui::DisplayFacade::GetVerticalResolution()
    {
        return display.Height();
    }

    infra::MemoryRange<embedded::lvgl::Color> Gui::DisplayFacade::GetBuffer1()
    {
        return infra::MakeRange(buffer1);
    }

    infra::MemoryRange<embedded::lvgl::Color> Gui::DisplayFacade::GetBuffer2()
    {
        return infra::MemoryRange<embedded::lvgl::Color>();
    }

    std::size_t Gui::DisplayFacade::PixelSize()
    {
        return display.PixelSize();
    }

    void Gui::DisplayFacade::Flush(embedded::lvgl::Area area, infra::MemoryRange<embedded::lvgl::Color> color, const infra::Function<void()>& onDone)
    {
        static_assert(sizeof(embedded::lvgl::Color) == sizeof(hal::Rgb565));

        hal::DisplayLcd::Area halArea{ static_cast<std::size_t>(area.x1), static_cast<std::size_t>(area.y1), static_cast<std::size_t>(area.x2), static_cast<std::size_t>(area.y2) };

        display.Flush(halArea, infra::ReinterpretCastMemoryRange<hal::Rgb565, embedded::lvgl::Color>(color), onDone);
    }

    Gui::Gui(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithMenu& terminal, services::Tracer& tracer, hal::DisplayLcd& display, hal::OutputPin& backlight)
        : services::TerminalCommandsAndMenu(terminal)
        , menu(name, description, *this)
        , terminal(terminal)
        , tracer(tracer)
        , backlight(backlight)
        , display(display)
        , displayLvgl(display)
        , gui(displayLvgl, inputDeviceLvgl)
    {
        terminal.AddMenu(menu);
        mainScreen.Emplace();
    }

    infra::MemoryRange<const services::TerminalCommands::Command> Gui::Commands()
    {
        //clang-format off
        static const std::array<Command, 4> commands = { {
            { { "d", "dim", "Show display dimensions [width, height] pixels" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
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
        //clang-format on

        return infra::MakeRange(commands);
    }

    services::TerminalCommandsAndMenu::MenuInfo& Gui::Menu()
    {
        return menu;
    }

    void Gui::GetDimensions(const infra::BoundedConstString& params)
    {
        tracer.Trace() << "Display LCD dimensions: [" << display.Width() << ", " << display.Height() << "]\r\n";
    }

    void Gui::DrawBackground(const infra::BoundedConstString& params)
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

    void Gui::Backlight(const infra::BoundedConstString& params)
    {
        backlight.Set(params == "on");
    }
}
