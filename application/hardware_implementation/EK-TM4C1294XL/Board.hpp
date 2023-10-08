#ifndef APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C1294XL_H
#define APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C1294XL_H

#include "application/hardware_abstraction/Hal.hpp"
#include "drivers/display/tft/Ssd2119.hpp"
#include "drivers/stepper_motor/Drv8711.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "hal/interfaces/RandomDataGenerator.hpp"
#include "hal_tiva/instantiations/EventInfrastructure.hpp"
#include "hal_tiva/instantiations/LaunchPadBsp.hpp"
#include "hal_tiva/instantiations/lwip/Ethernet.hpp"
#include "hal_tiva/synchronous_tiva/SynchronousSpiMaster.hpp"
#include "hal_tiva/tiva/Gpio.hpp"
#include "hal_tiva/tiva/QuadratureEncoder.hpp"
#include "hal_tiva/tiva/Uart.hpp"
#include "lwip/lwip_cpp/MulticastLwIp.hpp"
#include "services/network/Datagram.hpp"

namespace application
{
    class HardwareInitializationImpl
        : public HardwareInitialization
    {
    public:
        explicit HardwareInitializationImpl(const infra::Function<void()>& onDone);
        virtual ~HardwareInitializationImpl() = default;

        infra::EventDispatcherWithWeakPtr& EventDispatcher() override;

    private:
        infra::Optional<instantiations::EventInfrastructure> eventInfrastructure;
    };

    class HardwareAbstractionImpl
        : public HardwareAbstraction
    {
    public:
        explicit HardwareAbstractionImpl(const infra::Function<void()>& onDone);
        virtual ~HardwareAbstractionImpl() = default;

        services::Tracer& Tracer() override;
        services::TerminalWithMenu& Terminal() override;
        hal::GpioPin& DebugLed() override;

        OptionalForInterface<hal::DisplayLcd>& Display() override;
        OptionalForInterface<hal::OutputPin>& DisplayBackLight() override;
        infra::Optional<drivers::stepper_motor::Drv8711Sync>& DriverDrv8711() override;
        OptionalForInterface<hal::QuadratureEncoder>& EncoderMotor() override;
        OptionalForInterface<hal::QuadratureEncoder>& EncoderUser() override;
        OptionalForInterface<services::ConnectionFactory>& ConnectionFactory() override;
        OptionalForInterface<services::DatagramFactory>& UpdFactory() override;
        OptionalForInterface<services::Multicast>& MulticastFactory() override;

    private:
        class RandomDataGenerator
            : public hal::SynchronousRandomDataGenerator
        {
        public:
            RandomDataGenerator()
            {
                std::srand(0x1234);
            }

            void GenerateRandomData(infra::ByteRange result) override
            {
                auto data = std::rand();

                infra::ByteRange dataRange = infra::MakeByteRange(data);
                dataRange.shrink_from_back_to(result.size());

                std::copy(dataRange.begin(), dataRange.end(), result.begin());
                result.pop_front(dataRange.size());
            }
        };

        struct HwSsd2119
        {
            explicit HwSsd2119(const infra::Function<void()>& onDone)
                : display(spi, chipSelect, reset, dataOrCommand, onDone, displayConfig)
                , interface(display)
            { }

            hal::tiva::GpioPin reset{ hal::tiva::Port::K, 6 };
            hal::tiva::GpioPin dataOrCommand{ hal::tiva::Port::P, 4 };

            hal::tiva::GpioPin chipSelect{ hal::tiva::Port::P, 3 };

            hal::tiva::GpioPin clock{ hal::tiva::Port::Q, 0 };
            hal::tiva::GpioPin miso{ hal::tiva::Port::Q, 2 };
            hal::tiva::GpioPin mosi{ hal::tiva::Port::Q, 3 };

            hal::tiva::SynchronousSpiMaster::Config spiConfig{ true, true, 20000000 };
            hal::tiva::SynchronousSpiMaster spi{ 3, clock, miso, mosi, spiConfig };
            drivers::display::tft::Ssd2119Sync::Config displayConfig;
            drivers::display::tft::Ssd2119Sync display;
            OptionalForInterface<hal::DisplayLcd> interface;
        };

        struct Backlight
        {
            hal::tiva::GpioPin backLightPin{ hal::tiva::Port::G, 1 };
            hal::OutputPin backLight{ backLightPin };
            OptionalForInterface<hal::OutputPin> interface{ backLight };
        };

        struct HwDrv8711
        {
            explicit HwDrv8711(const infra::Function<void()>& onDone)
                : drv8711(infra::InPlace(), spi, chipSelect, reset, sleep, onDone)
            { }

            hal::tiva::GpioPin reset{ hal::tiva::Port::C, 7 };
            hal::tiva::GpioPin sleep{ hal::tiva::Port::E, 5 };
            hal::tiva::GpioPin direction{ hal::tiva::Port::B, 3 };

            hal::tiva::GpioPin chipSelect{ hal::tiva::Port::P, 2 };

            hal::tiva::GpioPin stallDetection{ hal::tiva::Port::M, 3 };
            hal::tiva::GpioPin fault{ hal::tiva::Port::H, 2 };

            hal::tiva::GpioPin clock{ hal::tiva::Port::D, 3 };
            hal::tiva::GpioPin miso{ hal::tiva::Port::D, 1 };
            hal::tiva::GpioPin mosi{ hal::tiva::Port::D, 0 };

            hal::tiva::SynchronousSpiMaster::Config spiConfig{ true, true, 20000000 };
            hal::tiva::SynchronousSpiMaster spi{ 2, clock, miso, mosi, spiConfig };
            infra::Optional<drivers::stepper_motor::Drv8711Sync> drv8711;
        };

        struct HwQuadratureInterface0
        {
            HwQuadratureInterface0()
                : encoder(peripheralIndex, phaseA, phaseB, index, config)
                , interface(encoder)
            {}

            const uint8_t peripheralIndex = 0;
            hal::tiva::GpioPin phaseA{ hal::tiva::Port::L, 1 };
            hal::tiva::GpioPin phaseB{ hal::tiva::Port::L, 2 };
            hal::tiva::GpioPin index{ hal::tiva::Port::L, 3 };
            hal::tiva::QuadratureEncoder::Config config;

            hal::tiva::QuadratureEncoder encoder;
            OptionalForInterface<hal::QuadratureEncoder> interface;
        };

        struct Ethernet
        {
            Ethernet(const hal::MacAddress& macAddress, const infra::BoundedString& hostname)
                : ethernet(leds, macAddress, hostname, randomDataGenerator)
                , connectionInterface(ethernet.lightweightIp)
                , datagramInterface(ethernet.lightweightIp)
                , multicastInterface(ethernet.lightweightIp)
            {}
            virtual ~Ethernet() = default;

            RandomDataGenerator randomDataGenerator;

            hal::tiva::GpioPin led0{ hal::tiva::Port::F, 0 };
            hal::tiva::GpioPin led1{ hal::tiva::Port::F, 4 };

            hal::tiva::Ethernet::Leds leds{ led0, led1, hal::tiva::dummyPin };

            instantiations::Ethernet<1, 1, 5> ethernet;
            OptionalForInterface<services::ConnectionFactory> connectionInterface;
            OptionalForInterface<services::DatagramFactory> datagramInterface;
            OptionalForInterface<services::Multicast> multicastInterface;
        };

        hal::MacAddress& GenerateMacAddress();
        infra::BoundedString& GetHostname();

        hal::MacAddress macAddress;
        infra::BoundedString::WithStorage<32> hostname;

        hal::tiva::Uart::Config terminalUartConfig{ false };
        hal::tiva::GpioPin& terminalUartTx = hal::tiva::dummyPin;
        hal::tiva::GpioPin terminalUartRx{ hal::tiva::Port::A, 0 };

        infra::Function<void()> onDone;
        instantiations::LaunchPadUi ui;
        instantiations::LaunchPadTerminalAndTracer tracer;
        hal::tiva::Uart terminalUart;
        services::TerminalWithMenu terminal;

        HwQuadratureInterface0 motorEncoder;
        Ethernet ethernet;
        HwSsd2119 hwSsd2119;
        Backlight backlight;
        infra::Optional<HwDrv8711> hwDrv8711;

        OptionalForInterface<hal::QuadratureEncoder> userEncoder;
    };
}

#endif
