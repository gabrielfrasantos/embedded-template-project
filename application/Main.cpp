#include BOARD_HEADER
#include "application/hardware_abstraction/Hal.hpp"
#include "application/parsers/Display.hpp"
#include "services/util/DebugLed.hpp"
#include "services/util/Terminal.hpp"

int main()
{
    static application::HardwareImplementation hw;

    hw.Initialize([]()
        {
            hw.Tracer().Trace() << "------------";
            hw.Tracer().Trace() << "|   TEST   |";
            hw.Tracer().Trace() << "------------";

            static services::DebugLed debugLed(hw.DebugLed(), std::chrono::milliseconds(100), std::chrono::milliseconds(1400));
            static application::parsers::Display parserDisplay("display", "Main display", hw.Terminal(), hw.Tracer(), hw.Display(), hw.DisplayBackLight());

            hw.Terminal().AddMenu(parserDisplay.Menu());
        });

    hw.EventDispatcher().Run();
    __builtin_unreachable();
}
