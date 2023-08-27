#include BOARD_HEADER
#include "application/hardware_abstraction/Hal.hpp"
#include "application/parsers/Display.hpp"
#include "services/util/DebugLed.hpp"

int main()
{
    static application::HardwareImplementation hw;

    hw.Initialize([]()
        {
            static services::DebugLed debugLed(hw.DebugLed(), std::chrono::milliseconds(100), std::chrono::milliseconds(1400));

            hw.Tracer().Trace() << "------------";
            hw.Tracer().Trace() << "|   TEST   |";
            hw.Tracer().Trace() << "------------";

            static application::parsers::Display parserDisplay(hw.Terminal(), hw.Tracer(), hw.Display(), hw.DisplayBackLight());
        });

    hw.EventDispatcher().Run();
    __builtin_unreachable();
}
