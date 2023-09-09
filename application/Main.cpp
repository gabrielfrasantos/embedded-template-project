#include BOARD_HEADER
#include "application/hardware_abstraction/Hal.hpp"
#include "application/parsers/Display.hpp"
#include "application/parsers/DriverDrv8711.hpp"
#include "application/parsers/QuadratureEncoder.hpp"
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
            static application::parsers::Drv8711 parserDrv8711("sm", "Driver DRV8711", hw.Terminal(), hw.Tracer());
            // static application::parsers::QuadratureEncoder parserQuadratureEncoderMotor("qeiMotor", "Motor encoder", hw.Terminal(), hw.Tracer());
            // static application::parsers::QuadratureEncoder parserQuadratureEncoderUser("qeiUser", "User encoder", hw.Terminal(), hw.Tracer());

            // external flash?
            // PWM?
            // littleFS with external flash?

            hw.Terminal().AddMenu(parserDisplay.Menu());
            hw.Terminal().AddMenu(parserDrv8711.Menu());
            // hw.Terminal().AddMenu(parserQuadratureEncoderMotor.Menu());
            // hw.Terminal().AddMenu(parserQuadratureEncoderUser.Menu());
        });

    hw.EventDispatcher().Run();
    __builtin_unreachable();
}
