#ifndef APPLICATION_HARDWARE_ABSTRACTION_H
#define APPLICATION_HARDWARE_ABSTRACTION_H

#include "drivers/stepper_motor/Drv8711.hpp"
#include "hal/interfaces/DisplayLcd.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "hal/interfaces/QuadratureEncoder.hpp"
#include "infra/event/EventDispatcherWithWeakPtr.hpp"
#include "infra/util/Function.hpp"
#include "services/network/Connection.hpp"
#include "services/util/Terminal.hpp"
#include "infra/util/Optional.hpp"

namespace application
{
    template<class T>
    class OptionalForInterface
    {
    public:
        explicit OptionalForInterface(T& interface)
            : initialized(true)
            , interface(&interface)
        {}

        OptionalForInterface()
            : interface(nullptr)
        {}

        OptionalForInterface(OptionalForInterface const &) = delete;
        OptionalForInterface(OptionalForInterface &&) = delete;
        OptionalForInterface& operator=(OptionalForInterface const &) = delete;
        OptionalForInterface& operator=(OptionalForInterface &&) = delete;

        const T& operator*() const
        {
            really_assert(initialized);
            return *interface;
        }

        T& operator*()
        {
            really_assert(initialized);
            return *interface;
        }

        const T* operator->() const
        {
            really_assert(initialized);
            return interface;
        }

        T* operator->()
        {
            really_assert(initialized);
            return interface;
        }

        explicit operator bool() const
        {
            return initialized;
        }

        bool operator!() const
        {
            return !initialized;
        }

        bool operator==(const OptionalForInterface& other) const
        {
            if (initialized && other.initialized)
                return **this == *other;
            else
                return initialized == other.initialized;
        }

        bool operator!=(const OptionalForInterface& other) const
        {
            return !(*this == other);
        }

        friend bool operator==(const OptionalForInterface& x, const infra::None&)
        {
            return !x;
        }

        friend bool operator!=(const OptionalForInterface& x, const infra::None& y)
        {
            return !(x == y);
        }

        friend bool operator==(const OptionalForInterface& x, const OptionalForInterface& y)
        {
            return y == x;
        }

        friend bool operator!=(const OptionalForInterface& x, const OptionalForInterface& y)
        {
            return y != x;
        }

        friend bool operator==(const OptionalForInterface& x, const T& y)
        {
            return x && *x == y;
        }

        friend bool operator!=(const OptionalForInterface& x, const T& y)
        {
            return !(x == y);
        }

        friend bool operator==(const T& x, const OptionalForInterface& y)
        {
            return y == x;
        }

        friend bool operator!=(const T& x, const OptionalForInterface& y)
        {
            return y != x;
        }

    private:
        bool initialized = false;
        T* interface;
    };

    class HardwareInitialization
    {
    public:
        virtual infra::EventDispatcherWithWeakPtr& EventDispatcher() = 0;
    };

    class HardwareAbstraction
    {
    public:
        virtual services::Tracer& Tracer() = 0;
        virtual services::TerminalWithMenu& Terminal() = 0;
        virtual hal::GpioPin& DebugLed() = 0;

        virtual OptionalForInterface<hal::DisplayLcd>& Display() = 0;
        virtual OptionalForInterface<hal::OutputPin>& DisplayBackLight() = 0;
        virtual infra::Optional<drivers::stepper_motor::Drv8711Sync>& DriverDrv8711() = 0;
        virtual OptionalForInterface<hal::QuadratureEncoder>& EncoderMotor() = 0;
        virtual OptionalForInterface<hal::QuadratureEncoder>& EncoderUser() = 0;
        virtual OptionalForInterface<services::ConnectionFactory>& ConnectionFactory() = 0;
    };
}

#endif
