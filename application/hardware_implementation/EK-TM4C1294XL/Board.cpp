#include "application/hardware_implementation/EK-TM4C1294XL/Board.hpp"

namespace application
{
    void HardwareImplementation::Initialize(const infra::Function<void()>& onDone)
    {
        this->onDone = onDone;
        hal::tiva::ConfigureClock(120000000, hal::tiva::crystalFrequency::_25_MHz);

        eventInfrastructure.Emplace();

        terminalUartConfig.enableTx = false;

        ui.Emplace();
        tracer.Emplace();
        terminalUart.Emplace(0, terminalUartTx, terminalUartRx, terminalUartConfig);
        terminal.Emplace(*terminalUart, tracer->tracer);

        backLight.Emplace(hwSsd2119.backLight);
        hwSsd2119.spi.Emplace(3, hwSsd2119.clock, hwSsd2119.miso, hwSsd2119.mosi, hwSsd2119.spiConfig);
        hwDrv8711.spi.Emplace(2, hwDrv8711.clock, hwDrv8711.miso, hwDrv8711.mosi, hwDrv8711.spiConfig);
        userEncoder.Emplace(qei0.peripheralIndex, qei0.phaseA, qei0.phaseB, qei0.index, userEncoderConfig);
        display.Emplace(
            *hwSsd2119.spi, hwSsd2119.chipSelect, hwSsd2119.reset, hwSsd2119.dataOrCommand, [this]()
            {
                drv8711.Emplace(*hwDrv8711.spi, hwDrv8711.chipSelect, hwDrv8711.reset, hwDrv8711.sleep, this->onDone);
            },
            displayConfig);
    }

    infra::EventDispatcherWithWeakPtr& HardwareImplementation::EventDispatcher()
    {
        return eventInfrastructure->eventDispatcher;
    }

    services::Tracer& HardwareImplementation::Tracer()
    {
        return tracer->tracerInfrastructure.tracer;
    }

    services::TerminalWithMenu& HardwareImplementation::Terminal()
    {
        return *terminal;
    }

    hal::GpioPin& HardwareImplementation::DebugLed()
    {
        return ui->led1;
    }

    hal::DisplayLcd& HardwareImplementation::Display()
    {
        return *display;
    }

    hal::OutputPin& HardwareImplementation::DisplayBackLight()
    {
        return *backLight;
    }

    drivers::stepper_motor::Drv8711Sync& HardwareImplementation::DriverDrv8711()
    {
        return *drv8711;
    }

    hal::QuadratureEncoder& HardwareImplementation::EncoderMotor()
    {
        return *motorEncoder;
    }

    hal::QuadratureEncoder& HardwareImplementation::EncoderUser()
    {
        return *userEncoder;
    }
}
