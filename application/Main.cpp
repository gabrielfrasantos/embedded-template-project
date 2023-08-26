#include BOARD_HEADER
#include "application/hardware_abstraction/Hal.hpp"
#include "services/util/DebugLed.hpp"
#include <ctime>

static std::size_t rand(std::size_t min, std::size_t max)
{
    return (std::rand() % max) + min;
}

int main()
{
    static application::HardwareImplementation hw;

    std::srand(321123);

    hw.Initialize([]()
        {
            static services::DebugLed debugLed(hw.DebugLed(), std::chrono::milliseconds(100), std::chrono::milliseconds(1400));

            hw.Tracer().Trace() << "------------";
            hw.Tracer().Trace() << "|   TEST   |";
            hw.Tracer().Trace() << "------------";

            hw.Display().DrawBackground(hal::Color(0x00, 0xff, 0x00), []()
                {
                    hw.DisplayBackLight().Set(true);

                    /*for (std::size_t i = 0; i < 320 * 240; i++)
                        hw.Display().DrawPixel({ rand(20, 280), rand(20, 200) }, hal::Color(rand(0, 0xffffff)), []() {});*/
                });
        });

    hw.EventDispatcher().Run();
    __builtin_unreachable();
}
