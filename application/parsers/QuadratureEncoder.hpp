#ifndef APPLICATION_PARSERS_QUADRATURE_ENCODER_HPP
#define APPLICATION_PARSERS_QUADRATURE_ENCODER_HPP

#include "hal/interfaces/QuadratureEncoder.hpp"
#include "services/tracer/TracerWithDateTime.hpp"
#include "services/util/Terminal.hpp"

namespace application::parsers
{
    class QuadratureEncoder
        : public services::TerminalCommandsAndMenu
    {
    public:
        QuadratureEncoder(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithMenu& terminal, services::Tracer& tracer, hal::QuadratureEncoder& quadratureEncoder);
        virtual ~QuadratureEncoder() = default;

        infra::MemoryRange<const services::TerminalCommands::Command> Commands() override;
        MenuInfo& Menu() override;

    private:
        MenuInfo menu;
        services::TerminalWithMenu& terminal;
        services::Tracer& tracer;
        hal::QuadratureEncoder& quadratureEncoder;

        void SetPosition(const infra::BoundedConstString& params);
        void SetResolution(const infra::BoundedConstString& params);
        void GetPosition();
        void GetResolution();
        void GetDirection();
        void GetSpeed();
    };
}

#endif
