#ifndef APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C123GXL_H
#define APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C123GXL_H

#include "application/hardware_abstraction/Hal.hpp"
#include "drivers/display/tft/Ssd2119.hpp"
#include "hal_tiva/instantiations/EventInfrastructure.hpp"
#include "hal_tiva/instantiations/LaunchPadBsp.hpp"
#include "hal_tiva/synchronous_tiva/SynchronousSpiMaster.hpp"
#include "hal_tiva/tiva/Clock.hpp"
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

        hal::GpioPin& DebugLed() override;
        hal::DisplayLcd& Display() override;
        hal::OutputPin& DisplayBackLight() override;

    private:
        instantiations::EventInfrastructure eventInfrastructure;
        infra::Optional<instantiations::LaunchPadUi> ui;
        infra::Optional<instantiations::LaunchPadTerminalAndTracer> tracer;

        hal::tiva::GpioPin reset{ hal::tiva::Port::D, 7 };
        hal::tiva::GpioPin dataOrCommand{ hal::tiva::Port::A, 5 };
        hal::tiva::GpioPin backLightDefinition{ hal::tiva::Port::F, 2 };

        hal::tiva::GpioPin clock{ hal::tiva::Port::B, 4 };
        hal::tiva::GpioPin miso{ hal::tiva::Port::B, 6 };
        hal::tiva::GpioPin mosi{ hal::tiva::Port::B, 7 };
        hal::tiva::GpioPin chipSelect{ hal::tiva::Port::A, 4 };

        hal::tiva::SynchronousSpiMaster::Config spiConfig{ true, true, 20000000 };
        infra::Optional<hal::tiva::SynchronousSpiMaster> spi;

        infra::Optional<hal::OutputPin> backLight;
        drivers::display::tft::Ssd2119Sync::Config displayConfig;
        infra::Optional<drivers::display::tft::Ssd2119Sync> display;
    };
}

#endif
