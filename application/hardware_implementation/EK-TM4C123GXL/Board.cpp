#include "application/hardware_implementation/EK-TM4C123GXL/Board.hpp"

namespace application
{
    void HardwareImplementation::Initialize(const infra::Function<void()>& onDone)
    {
        this->onDone = onDone;
        hal::tiva::ConfigureClock(hal::tiva::crystalFrequency::_16_MHz, hal::tiva::oscillatorSource::main);

        terminalUartConfig.enableTx = false;

        ui.Emplace();
        tracer.Emplace();
        terminalUart.Emplace(0, terminalUartTx, terminalUartRx, terminalUartConfig);
        terminal.Emplace(*terminalUart, tracer->tracer);

        backLight.Emplace(hwSsd2119.backLight);
        spi.Emplace(2, clock, miso, mosi, spiConfig);
        userEncoder.Emplace(qei0.peripheralIndex, qei0.phaseA, qei0.phaseB, qei0.index, userEncoderConfig);
        motorEncoder.Emplace(qei1.peripheralIndex, qei1.phaseA, qei1.phaseB, qei1.index, motorEncoderConfig);
        display.Emplace(
            *spi, hwSsd2119.chipSelect, hwSsd2119.reset, hwSsd2119.dataOrCommand, [this]()
            {
                drv8711.Emplace(*spi, hwDrv8711.chipSelect, hwDrv8711.reset, hwDrv8711.sleep, this->onDone);
            },
            displayConfig);
    }

    infra::EventDispatcherWithWeakPtr& HardwareImplementation::EventDispatcher()
    {
        return eventInfrastructure.eventDispatcher;
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

    drivers::stepper_motor::Drv8711Sync& HardwareImplementation::DriverDrv8711()
    {
        return *drv8711;
    }

    hal::QuadratureEncoder& HardwareImplementation::EncoderMotor()
    {
        return *userEncoder;
    }

    hal::QuadratureEncoder& HardwareImplementation::EncoderUser()
    {
        return *motorEncoder;
    }
}
