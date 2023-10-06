#include "application/parsers/QuadratureEncoder.hpp"

namespace application::parsers
{
    QuadratureEncoder::QuadratureEncoder(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithMenu& terminal, services::Tracer& tracer, hal::QuadratureEncoder& quadratureEncoder)
        : services::TerminalCommandsAndMenu(terminal)
        , menu(name, description, *this)
        , terminal(terminal)
        , tracer(tracer)
        , quadratureEncoder(quadratureEncoder)
    {
        terminal.AddMenu(menu);
    }

    infra::MemoryRange<const services::TerminalCommands::Command> QuadratureEncoder::Commands()
    {
        //clang-format off
        static const std::array<Command, 6> commands = { {
            { { "sp", "set_pos", "Set encoder position [0;0xffffffff]" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->SetPosition(params);
                } },
            { { "sr", "set_res", "Set encoder resolution [0;0xffffffff]" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->SetResolution(params);
                } },
            { { "gp", "get_pos", "Get encoder position" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->GetPosition();
                } },
            { { "gr", "get_res", "Get encoder resolution" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->GetResolution();
                } },
            { { "d", "direction", "Get movement direction" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->GetDirection();
                } },
            { { "s", "speed", "Get speed" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->GetSpeed();
                } },
        } };
        //clang-format on

        return infra::MakeRange(commands);
    }

    services::TerminalCommandsAndMenu::MenuInfo& QuadratureEncoder::Menu()
    {
        return menu;
    }

    void QuadratureEncoder::SetPosition(const infra::BoundedConstString& params)
    {
    }

    void QuadratureEncoder::SetResolution(const infra::BoundedConstString& params)
    {
    }

    void QuadratureEncoder::GetPosition()
    {
        tracer.Trace() << "Encoder position: " << quadratureEncoder.Position();
    }

    void QuadratureEncoder::GetResolution()
    {
        tracer.Trace() << "Encoder resolution: " << quadratureEncoder.Position();
    }

    void QuadratureEncoder::GetDirection()
    {
        tracer.Trace() << "Encoder direction: " << quadratureEncoder.Direction();
    }

    void QuadratureEncoder::GetSpeed()
    {
        tracer.Trace() << "Encoder speed: " << quadratureEncoder.Speed();
    }
}
