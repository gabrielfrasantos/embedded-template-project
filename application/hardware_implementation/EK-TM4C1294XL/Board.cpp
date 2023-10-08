#include "application/hardware_implementation/EK-TM4C1294XL/Board.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "hal_tiva/tiva/ClockTm4c129.hpp"
#include "hal_tiva/tiva/UniqueDeviceId.hpp"
#include "infra/stream/StringOutputStream.hpp"

namespace application
{
    HardwareInitializationImpl::HardwareInitializationImpl(const infra::Function<void()>& onDone)
    {
        hal::tiva::ConfigureClock(120000000, hal::tiva::crystalFrequency::_25_MHz);

        eventInfrastructure.Emplace();

        onDone();
    }

    infra::EventDispatcherWithWeakPtr& HardwareInitializationImpl::EventDispatcher()
    {
        return eventInfrastructure->eventDispatcher;
    }

    HardwareAbstractionImpl::HardwareAbstractionImpl(const infra::Function<void()>& onDone)
        : onDone(onDone)
        , terminalUart(0, terminalUartTx, terminalUartRx, terminalUartConfig)
        , terminal(terminalUart, tracer.tracer)
        , ethernet(GenerateMacAddress(), GetHostname())
        , hwSsd2119([this]()
            {
                this->hwDrv8711.Emplace(this->onDone);
            })
    { }

    hal::MacAddress& HardwareAbstractionImpl::GenerateMacAddress()
    {
        auto uniqueDeviceId = hal::tiva::UniqueDeviceId();

        for (int i = 0; i != std::tuple_size<hal::MacAddress>::value; ++i)
            macAddress[i] = uniqueDeviceId[i];

        macAddress[0] &= 0xfe; // unicast
        macAddress[0] |= 0x02; // locally administered

        return macAddress;
    }

    infra::BoundedString& HardwareAbstractionImpl::GetHostname()
    {
        infra::StringOutputStream stream(hostname);

        stream << "tiva-";
        for (int i = 0; i != macAddress.size(); ++i)
            stream << infra::hex << infra::Width(2, '0') << macAddress[i];

        return hostname;
    }

    services::Tracer& HardwareAbstractionImpl::Tracer()
    {
        return tracer.tracerInfrastructure.tracer;
    }

    services::TerminalWithMenu& HardwareAbstractionImpl::Terminal()
    {
        return terminal;
    }

    hal::GpioPin& HardwareAbstractionImpl::DebugLed()
    {
        return ui.led1;
    }

    OptionalForInterface<hal::DisplayLcd>& HardwareAbstractionImpl::Display()
    {
        return hwSsd2119.interface;
    }

    OptionalForInterface<hal::OutputPin>& HardwareAbstractionImpl::DisplayBackLight()
    {
        return backlight.interface;
    }

    infra::Optional<drivers::stepper_motor::Drv8711Sync>& HardwareAbstractionImpl::DriverDrv8711()
    {
        return hwDrv8711->drv8711;
    }

    OptionalForInterface<hal::QuadratureEncoder>& HardwareAbstractionImpl::EncoderMotor()
    {
        return motorEncoder.interface;
    }

    OptionalForInterface<hal::QuadratureEncoder>& HardwareAbstractionImpl::EncoderUser()
    {
        return userEncoder;
    }

    OptionalForInterface<services::ConnectionFactory>& HardwareAbstractionImpl::ConnectionFactory()
    {
        return ethernet.connectionInterface;
    }

    OptionalForInterface<services::DatagramFactory>& HardwareAbstractionImpl::UpdFactory()
    {
        return ethernet.datagramInterface;
    }

    OptionalForInterface<services::Multicast>& HardwareAbstractionImpl::MulticastFactory()
    {
        return ethernet.multicastInterface;
    }
}
