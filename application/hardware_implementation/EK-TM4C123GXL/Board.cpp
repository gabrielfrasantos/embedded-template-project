#include "application/hardware_implementation/EK-TM4C123GXL/Board.hpp"

namespace application
{
    void HardwareImplementation::Initialize(const infra::Function<void()>& onDone)
    {
        hal::tiva::ConfigureClock(hal::tiva::crystalFrequency::_16_MHz, hal::tiva::oscillatorSource::main);

        ui.Emplace();
        tracer.Emplace();

        backLight.Emplace(backLightDefinition);
        spi.Emplace(2, clock, miso, mosi, spiConfig);
        display.Emplace(*spi, chipSelect, reset, dataOrCommand, onDone, displayConfig);
    }

    infra::EventDispatcherWithWeakPtr& HardwareImplementation::EventDispatcher()
    {
        return eventInfrastructure.eventDispatcher;
    }

    services::Tracer& HardwareImplementation::Tracer()
    {
        return tracer->tracerInfrastructure.tracer;
    }

    hal::GpioPin& HardwareImplementation::DebugLed()
    {
        return ui->ledGreen;
    }

    hal::DisplayLcd& HardwareImplementation::Display()
    {
        return *display;
    }

    hal::OutputPin& HardwareImplementation::DisplayBackLight()
    {
        return *backLight;
    }
}
