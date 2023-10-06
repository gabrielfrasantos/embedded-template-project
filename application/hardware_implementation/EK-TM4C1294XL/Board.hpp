#ifndef APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C1294XL_H
#define APPLICATION_HARDWARE_IMPLEMENTATION_EK_TM4C1294XL_H

#include "application/hardware_abstraction/Hal.hpp"
#include "drivers/display/tft/Ssd2119.hpp"
#include "drivers/stepper_motor/Drv8711.hpp"
#include "hal/interfaces/RandomDataGenerator.hpp"
#include "hal_tiva/instantiations/EventInfrastructure.hpp"
#include "hal_tiva/instantiations/LaunchPadBsp.hpp"
#include "hal_tiva/instantiations/lwip/Ethernet.hpp"
#include "hal_tiva/instantiations/lwip/EthernetSmiObserver.hpp"
#include "hal_tiva/synchronous_tiva/SynchronousSpiMaster.hpp"
#include "hal_tiva/tiva/ClockTm4c129.hpp"
#include "hal_tiva/tiva/Gpio.hpp"
#include "hal_tiva/tiva/QuadratureEncoder.hpp"
#include "hal_tiva/tiva/Uart.hpp"
#include "hal_tiva/tiva/UniqueDeviceId.hpp"
#include "infra/stream/StringOutputStream.hpp"
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
        drivers::stepper_motor::Drv8711Sync& DriverDrv8711() override;
        hal::QuadratureEncoder& EncoderMotor() override;
        hal::QuadratureEncoder& EncoderUser() override;
        services::ConnectionFactory& ConnectionFactory() override;

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
            hal::tiva::GpioPin reset{ hal::tiva::Port::K, 6 };
            hal::tiva::GpioPin dataOrCommand{ hal::tiva::Port::P, 4 };
            hal::tiva::GpioPin backLight{ hal::tiva::Port::G, 1 };

            hal::tiva::GpioPin chipSelect{ hal::tiva::Port::P, 3 };

            hal::tiva::GpioPin clock{ hal::tiva::Port::Q, 0 };
            hal::tiva::GpioPin miso{ hal::tiva::Port::Q, 2 };
            hal::tiva::GpioPin mosi{ hal::tiva::Port::Q, 3 };

            hal::tiva::SynchronousSpiMaster::Config spiConfig{ true, true, 20000000 };
            infra::Optional<hal::tiva::SynchronousSpiMaster> spi;
        };

        struct HwDrv8711
        {
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
            infra::Optional<hal::tiva::SynchronousSpiMaster> spi;
        };

        struct Ethernet
        {
            Ethernet(const hal::MacAddress& macAddress, const infra::BoundedString& hostname)
                : ethernet(leds, macAddress, hostname, randomDataGenerator)
            {}

            RandomDataGenerator randomDataGenerator;

            hal::tiva::GpioPin led0{ hal::tiva::Port::F, 0 };
            hal::tiva::GpioPin led1{ hal::tiva::Port::F, 4 };

            hal::tiva::Ethernet::Leds leds{ led0, led1, hal::tiva::dummyPin };

            instantiations::Ethernet<1, 1, 5> ethernet;
        };

        struct HwQuadratureInterface0
        {
            const uint8_t peripheralIndex = 0;
            hal::tiva::GpioPin phaseA{ hal::tiva::Port::L, 1 };
            hal::tiva::GpioPin phaseB{ hal::tiva::Port::L, 2 };
            hal::tiva::GpioPin index{ hal::tiva::Port::L, 3 };
        };

        hal::MacAddress macAddress;
        infra::BoundedString::WithStorage<32> hostname;

        infra::Function<void()> onDone;
        infra::Optional<instantiations::EventInfrastructure> eventInfrastructure;
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

        drivers::display::tft::Ssd2119Sync::Config displayConfig;
        infra::Optional<hal::OutputPin> backLight;
        infra::Optional<drivers::display::tft::Ssd2119Sync> display;
        infra::Optional<drivers::stepper_motor::Drv8711Sync> drv8711;
        hal::tiva::QuadratureEncoder::Config userEncoderConfig;
        hal::tiva::QuadratureEncoder::Config motorEncoderConfig;
        infra::Optional<hal::tiva::QuadratureEncoder> userEncoder;
        infra::Optional<hal::tiva::QuadratureEncoder> motorEncoder;
        infra::Optional<Ethernet> ethernet;
    };
}

#endif
