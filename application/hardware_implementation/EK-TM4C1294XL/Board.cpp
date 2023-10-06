#include "application/hardware_implementation/EK-TM4C1294XL/Board.hpp"

namespace
{
    void LoadEthernetConfiguration(hal::MacAddress& macAddress, infra::BoundedString& hostname)
    {
        auto uniqueDeviceId = hal::tiva::UniqueDeviceId();

        for (int i = 0; i != std::tuple_size<hal::MacAddress>::value; ++i)
            macAddress[i] = uniqueDeviceId[i];

        macAddress[0] &= 0xfe; // unicast
        macAddress[0] |= 0x02; // locally administered

        infra::StringOutputStream stream(hostname);

        stream << "tiva-";
        for (int i = 0; i != macAddress.size(); ++i)
            stream << infra::hex << infra::Width(2, '0') << macAddress[i];
    }
}

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

        LoadEthernetConfiguration(macAddress, hostname);

        backLight.Emplace(hwSsd2119.backLight);
        hwSsd2119.spi.Emplace(3, hwSsd2119.clock, hwSsd2119.miso, hwSsd2119.mosi, hwSsd2119.spiConfig);
        hwDrv8711.spi.Emplace(2, hwDrv8711.clock, hwDrv8711.miso, hwDrv8711.mosi, hwDrv8711.spiConfig);
        userEncoder.Emplace(qei0.peripheralIndex, qei0.phaseA, qei0.phaseB, qei0.index, userEncoderConfig);
        ethernet.Emplace(macAddress, hostname);
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

    services::ConnectionFactory& HardwareImplementation::ConnectionFactory()
    {
        return ethernet->ethernet.lightweightIp;
    }
}
