#ifndef APPLICATION_HARDWARE_ABSTRACTION_H
#define APPLICATION_HARDWARE_ABSTRACTION_H

#include "hal/interfaces/DisplayLcd.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "infra/event/EventDispatcherWithWeakPtr.hpp"
#include "infra/util/Function.hpp"
#include "services/tracer/TracerWithDateTime.hpp"
#include "services/util/Terminal.hpp"

namespace application
{
    class HardwareAbstraction
    {
    public:
        virtual void Initialize(const infra::Function<void()>& onDone) = 0;
        virtual infra::EventDispatcherWithWeakPtr& EventDispatcher() = 0;
        virtual services::Tracer& Tracer() = 0;
        virtual services::TerminalWithCommands& Terminal() = 0;
        virtual hal::GpioPin& DebugLed() = 0;

        virtual hal::DisplayLcd& Display() = 0;
        virtual hal::OutputPin& DisplayBackLight() = 0;
    };
}

#endif
