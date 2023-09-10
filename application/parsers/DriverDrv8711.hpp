#ifndef APPLICATION_PARSERS_DRV8711_HPP
#define APPLICATION_PARSERS_DRV8711_HPP

#include "drivers/stepper_motor/Drv8711.hpp"
#include "services/tracer/TracerWithDateTime.hpp"
#include "services/util/Terminal.hpp"

namespace application::parsers
{
    class Drv8711
        : public services::TerminalCommandsAndMenu
    {
    public:
        Drv8711(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithCommands& terminal, services::Tracer& tracer, drivers::stepper_motor::Drv8711Sync& drv8711);
        virtual ~Drv8711() = default;

        infra::MemoryRange<const services::TerminalCommands::Command> Commands() override;
        MenuInfo& Menu() override;

    private:
        MenuInfo menu;
        services::TerminalWithCommands& terminal;
        services::Tracer& tracer;
        drivers::stepper_motor::Drv8711Sync& drv8711;

        void ReadControl();
        void ReadTorque();
        void ReadOff();
        void ReadBlank();
        void ReadDecay();
        void ReadStall();
        void ReadDrive();
        void ReadStatus();
    };
}

#endif
