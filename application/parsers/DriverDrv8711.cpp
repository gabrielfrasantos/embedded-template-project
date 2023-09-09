#include "application/parsers/DriverDrv8711.hpp"

namespace application::parsers
{
    Drv8711::Drv8711(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithCommands& terminal, services::Tracer& tracer)
        : services::TerminalCommandsAndMenu(terminal)
        , menu(name, description, *this)
        , terminal(terminal)
        , tracer(tracer)
    {}

    infra::MemoryRange<const services::TerminalCommands::Command> Drv8711::Commands()
    {
        //clang-format off
        static const std::array<Command, 8> commands = { {
            { { "rc", "read_control", "Read register control" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadControl();
                } },
            { { "rt", "read_torque", "Read register torque" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadTorque();
                } },
            { { "ro", "read_off", "Read register off" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadOff();
                } },
            { { "rb", "read_blank", "Read register blank" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadBlank();
                } },
            { { "rdc", "read_decay", "Read register decay" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadDecay();
                } },
            { { "rsl", "read_stall", "Read register stall" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadStall();
                } },
            { { "rdr", "read_drive", "Read register drive" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadDrive();
                } },
            { { "rst", "read_status", "Read register status" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadStatus();
                } },
        } };
        //clang-format on

        return infra::MakeRange(commands);
    }

    services::TerminalCommandsAndMenu::MenuInfo& Drv8711::Menu()
    {
        return menu;
    }

    void Drv8711::ReadControl()
    {
    }

    void Drv8711::ReadTorque()
    {
    }

    void Drv8711::ReadOff()
    {
    }

    void Drv8711::ReadBlank()
    {
    }

    void Drv8711::ReadDecay()
    {
    }

    void Drv8711::ReadStall()
    {
    }

    void Drv8711::ReadDrive()
    {
    }

    void Drv8711::ReadStatus()
    {
    }
}
