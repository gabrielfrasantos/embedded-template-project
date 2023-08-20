#include "hal_tiva/instantiations/EventInfrastructure.hpp"
#include "hal_tiva/instantiations/LaunchPadBsp.hpp"
#include "services/util/DebugLed.hpp"
#include "hal_tiva/tiva/Clock.hpp"
#include "drivers/display/tft/Ssd2119.hpp"
#include "hal_tiva/synchronous_tiva/SynchronousSpiMaster.hpp"
#include <ctime>

static std::size_t rand(std::size_t min, std::size_t max)
{
    return (std::rand() % max) + min;
}

int main()
{
    hal::tiva::ConfigureClock(hal::tiva::crystalFrequency::_16_MHz, hal::tiva::oscillatorSource::main);

    static instantiations::EventInfrastructure eventInfrastructure;
    static instantiations::LaunchPadUi ui;
    static instantiations::LaunchPadTerminalAndTracer tracer;
    static services::DebugLed debugLed(ui.ledGreen, std::chrono::milliseconds(100), std::chrono::milliseconds(1400));

    tracer.tracer.Trace() << "------------";
    tracer.tracer.Trace() << "|   TEST   |";
    tracer.tracer.Trace() << "------------";

    hal::tiva::GpioPin clock(hal::tiva::Port::B, 4);
    hal::tiva::GpioPin miso(hal::tiva::Port::B, 6);
    hal::tiva::GpioPin mosi(hal::tiva::Port::B, 7);
    hal::tiva::GpioPin chipSelect(hal::tiva::Port::A, 4);

    hal::tiva::GpioPin reset(hal::tiva::Port::D, 7);
    hal::tiva::GpioPin dataOrCommand(hal::tiva::Port::A, 5);
    hal::tiva::GpioPin backLightDefinition(hal::tiva::Port::F, 2);

    static hal::OutputPin backLight(backLightDefinition);

    hal::tiva::SynchronousSpiMaster::Config spiConfig;
    spiConfig.baudRate = 40000000;
    hal::tiva::SynchronousSpiMaster spi(2, clock, miso, mosi, spiConfig);

    std::srand(321123);

    static drivers::display::tft::Ssd2119Sync display(spi, chipSelect, reset, dataOrCommand, []()
        {
            display.DrawBackground(drivers::display::tft::Color(0xff, 0xff, 0xff), []()
                {
                    backLight.Set(true);

                    for (std::size_t i = 0; i < 320 * 240; i++)
                        display.DrawPixel(rand(20, 240), rand(20, 200), drivers::display::tft::Color(rand(0, 0xffffff)), [](){});
                });
        });

    eventInfrastructure.Run();
    __builtin_unreachable();
}
