#ifndef APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C123GXL_H
#define APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C123GXL_H

#include "application/hardware_abstraction/Hal.hpp"
#include "drivers/display/tft/Ssd2119.hpp"
#include "drivers/stepper_motor/Drv8711.hpp"
#include "hal_tiva/instantiations/EventInfrastructure.hpp"
#include "hal_tiva/instantiations/LaunchPadBsp.hpp"
#include "hal_tiva/synchronous_tiva/SynchronousSpiMaster.hpp"
#include "hal_tiva/tiva/Clock.hpp"
#include "hal_tiva/tiva/Uart.hpp"
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
        drivers::stepper_motor::Drv8711Sync& DriverDrv8711();

    private:
        struct HwSsd2119
        {
            hal::tiva::GpioPin reset{ hal::tiva::Port::B, 0 };
            hal::tiva::GpioPin dataOrCommand{ hal::tiva::Port::B, 1 };
            hal::tiva::GpioPin backLight{ hal::tiva::Port::F, 2 };

            hal::tiva::GpioPin chipSelect{ hal::tiva::Port::E, 4 };

            // variant<Gpio, Pwm> a1_step
            // variant<Gpio, Pwm> a2_direction
            // variant<Gpio, Pwm> b1
            // variant<Gpio, Pwm> b2
        };

        struct HwDrv8711
        {
            hal::tiva::GpioPin reset{ hal::tiva::Port::A, 5 };
            hal::tiva::GpioPin sleep{ hal::tiva::Port::E, 5 };
            hal::tiva::GpioPin direction{ hal::tiva::Port::F, 2 };

            hal::tiva::GpioPin chipSelect{ hal::tiva::Port::A, 2 };

            hal::tiva::GpioPin stallDetection{ hal::tiva::Port::B, 2 };
            hal::tiva::GpioPin fault{ hal::tiva::Port::E, 0 };
        };

        struct HwQuadratureInterface0
        {
            hal::tiva::GpioPin phaseA{ hal::tiva::Port::D, 6 };
            hal::tiva::GpioPin phaseB{ hal::tiva::Port::D, 7 };
            hal::tiva::GpioPin index{ hal::tiva::Port::D, 3 };
        };

        struct HwQuadratureInterface1
        {
            hal::tiva::GpioPin phaseA{ hal::tiva::Port::C, 5 };
            hal::tiva::GpioPin phaseB{ hal::tiva::Port::C, 6 };
            hal::tiva::GpioPin index{ hal::tiva::Port::C, 4 };
        };

        infra::Function<void()> onDone;
        instantiations::EventInfrastructure eventInfrastructure;
        infra::Optional<instantiations::LaunchPadUi> ui;
        infra::Optional<instantiations::LaunchPadTerminalAndTracer> tracer;
        hal::tiva::Uart::Config terminalUartConfig;
        infra::Optional<hal::tiva::Uart> terminalUart;
        infra::Optional<services::TerminalWithMenu> terminal;

        hal::tiva::GpioPin& terminalUartTx = hal::tiva::dummyPin;
        hal::tiva::GpioPin terminalUartRx{ hal::tiva::Port::A, 0 };

        HwSsd2119 hwSsd2119;
        HwDrv8711 hwDrv8711;
        HwQuadratureInterface0 qei0;
        HwQuadratureInterface0 qei1;

        hal::tiva::GpioPin clock{ hal::tiva::Port::B, 4 };
        hal::tiva::GpioPin miso{ hal::tiva::Port::B, 6 };
        hal::tiva::GpioPin mosi{ hal::tiva::Port::B, 7 };

        hal::tiva::SynchronousSpiMaster::Config spiConfig{ true, true, 20000000 };
        infra::Optional<hal::tiva::SynchronousSpiMaster> spi;

        drivers::display::tft::Ssd2119Sync::Config displayConfig;
        infra::Optional<hal::OutputPin> backLight;
        infra::Optional<drivers::display::tft::Ssd2119Sync> display;
        infra::Optional<drivers::stepper_motor::Drv8711Sync> drv8711;
    };
}

#endif
