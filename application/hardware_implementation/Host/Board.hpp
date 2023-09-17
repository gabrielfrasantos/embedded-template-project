#ifndef APPLICATION_HARDWARE_IMPLEMENTATION_HOST_H
#define APPLICATION_HARDWARE_IMPLEMENTATION_HOST_H

#include "application/hardware_abstraction/Hal.hpp"
#include "drivers/display/tft/Ssd2119.hpp"
#include "drivers/stepper_motor/Drv8711.hpp"
#include "infra/util/Optional.hpp"

namespace application
{
    class HardwareImplementation
        : public HardwareAbstraction
    {
    public:
        virtual ~HardwareImplementation() = default;

        void Initialize(const infra::Function<void()>& onDone) override;
        infra::EventDispatcherWithWeakPtr& EventDispatcher() override;
        services::Tracer& Tracer() override;
        services::TerminalWithMenu& Terminal() override;
        hal::GpioPin& DebugLed() override;

        hal::DisplayLcd& Display() override;
        hal::OutputPin& DisplayBackLight() override;
        hal::QuadratureEncoder& EncoderMotor() override;
        hal::QuadratureEncoder& EncoderUser() override;

    private:
    };
}

#endif
