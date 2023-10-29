#include BOARD_HEADER
#include "application/parsers/Display.hpp"
#include "application/parsers/DriverDrv8711.hpp"
#include "application/parsers/QuadratureEncoder.hpp"
#include "services/util/DebugLed.hpp"

int main()
{
    static application::HardwareInitializationImpl initialization([]()
        {
            static application::HardwareAbstractionImpl hw([]()
                {
                    hw.Tracer().Trace() << "--------------------------------------------------------";
                    hw.Tracer().Trace() << " application name    : " << infra::Width(32, ' ') << "reference project";
                    hw.Tracer().Trace() << " version             : " << infra::Width(32, ' ') << "0.0.0";
                    hw.Tracer().Trace() << " commit              : " << infra::Width(32, ' ') << "deadbeef";
                    hw.Tracer().Trace() << " hardware            : " << infra::Width(32, ' ') << "ek-tm4c123g-custom";
                    hw.Tracer().Trace() << "--------------------------------------------------------";

                    static services::DebugLed debugLed(hw.DebugLed(), std::chrono::milliseconds(100), std::chrono::milliseconds(1400));


                    if (hw.Display() && hw.DisplayBackLight())
                        static application::parsers::Display parserDisplay("display", "Main display", hw.Terminal(), hw.Tracer(), *hw.Display(), *hw.DisplayBackLight());

                    if (hw.DriverDrv8711())
                        static application::parsers::Drv8711 parserDrv8711("sm", "Driver DRV8711", hw.Terminal(), hw.Tracer(), *hw.DriverDrv8711());

                    if (hw.EncoderUser())
                        static application::parsers::QuadratureEncoder parserQuadratureEncoderUser("qei_user", "User encoder", hw.Terminal(), hw.Tracer(), *hw.EncoderUser());

                    if (hw.EncoderMotor())
                        static application::parsers::QuadratureEncoder parserQuadratureEncoderMotor("qei_motor", "Motor encoder", hw.Terminal(), hw.Tracer(), *hw.EncoderMotor());

                    // USB host
                    // external flash?
                    // PWM?
                    // littleFS with external flash?

                    hw.Terminal().PrintHelp();
                });
        });

    initialization.EventDispatcher().Run();
    __builtin_unreachable();
}
