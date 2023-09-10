#include "application/parsers/DriverDrv8711.hpp"

namespace infra
{
    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Control::AmplifierGain& amplifierGain)
    {
        switch (amplifierGain)
        {
            case drivers::stepper_motor::Drv8711Sync::Control::AmplifierGain::_5:
                stream << "5";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::AmplifierGain::_10:
                stream << "10";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::AmplifierGain::_20:
                stream << "20";
                break;
            default:
                stream << "40";
                break;
        }

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Control::DeadTime& deadTime)
    {
        switch (deadTime)
        {
            case drivers::stepper_motor::Drv8711Sync::Control::DeadTime::_400ns:
                stream << "400 ns";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::DeadTime::_450ns:
                stream << "450 ns";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::DeadTime::_650ns:
                stream << "650 ns";
                break;
            default:
                stream << "850 ns";
                break;
        }

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Control::StallDetection& stall)
    {
        if (stall == drivers::stepper_motor::Drv8711Sync::Control::StallDetection::external)
            stream << "external";
        else
            stream << "internal";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Control::Direction direction)
    {
        if (direction == drivers::stepper_motor::Drv8711Sync::Control::Direction::direct)
            stream << "direct";
        else
            stream << "reverse";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Control::Step& step)
    {
        switch (step)
        {
            case drivers::stepper_motor::Drv8711Sync::Control::Step::full:
                stream << "full";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::Step::half:
                stream << "half";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::Step::_1_4:
                stream << "1/4";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::Step::_1_8:
                stream << "1/8";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::Step::_1_16:
                stream << "1/16";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::Step::_1_32:
                stream << "1/32";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::Step::_1_64:
                stream << "1/64";
                break;
            case drivers::stepper_motor::Drv8711Sync::Control::Step::_1_128:
                stream << "1/128";
                break;
            default:
                stream << "1/256";
                break;
        }

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold& smplth)
    {
        switch (smplth)
        {
            case drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold::_50us:
                stream << "50";
                break;
            case drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold::_100us:
                stream << "100";
                break;
            case drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold::_200us:
                stream << "200";
                break;
            case drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold::_300us:
                stream << "300";
                break;
            case drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold::_400us:
                stream << "400";
                break;
            case drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold::_600us:
                stream << "600";
                break;
            case drivers::stepper_motor::Drv8711Sync::Torque::BackEMFSampleThreshold::_800us:
                stream << "800";
                break;
            default:
                stream << "1000";
                break;
        }

        stream << " us";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Off::PwmMode& pwmMode)
    {
        if (pwmMode == drivers::stepper_motor::Drv8711Sync::Off::PwmMode::externalControl)
            stream << "external control";
        else
            stream << "internal control";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Decay::Mode& mode)
    {
        switch (mode)
        {
            case drivers::stepper_motor::Drv8711Sync::Decay::Mode::forceSlow:
                stream << "Force slow decay at all times";
                break;
            case drivers::stepper_motor::Drv8711Sync::Decay::Mode::slowForIncreasingMixedForDecreasing:
                stream << "Slow decay for increasing current, mixed decay for decreasing current";
                break;
            case drivers::stepper_motor::Drv8711Sync::Decay::Mode::forceFast:
                stream << "Force fast decay at all times";
                break;
            case drivers::stepper_motor::Drv8711Sync::Decay::Mode::mixed:
                stream << "Mixed decay at all times";
                break;
            case drivers::stepper_motor::Drv8711Sync::Decay::Mode::slowForIncreasingAutoForDecreasing:
                stream << "Slow decay for increasing current, auto mixed decay for decreasing current";
                break;
            default:
                stream << "Auto mixed decay at all times";
                break;
        }

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Stall::AssertCounter& counter)
    {
        switch (counter)
        {
            case drivers::stepper_motor::Drv8711Sync::Stall::AssertCounter::one:
                stream << "On 1 step";
                break;
            case drivers::stepper_motor::Drv8711Sync::Stall::AssertCounter::two:
                stream << "On 2 steps";
                break;
            case drivers::stepper_motor::Drv8711Sync::Stall::AssertCounter::four:
                stream << "On 4 steps";
                break;
            default:
                stream << "On 8 steps";
                break;
        }

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Stall::BackEMFDivisor& divisor)
    {
        switch (divisor)
        {
            case drivers::stepper_motor::Drv8711Sync::Stall::BackEMFDivisor::_4:
                stream << "Back EMF divided by 4";
                break;
            case drivers::stepper_motor::Drv8711Sync::Stall::BackEMFDivisor::_8:
                stream << "Back EMF divided by 8";
                break;
            case drivers::stepper_motor::Drv8711Sync::Stall::BackEMFDivisor::_16:
                stream << "Back EMF divided by 16";
                break;
            default:
                stream << "Back EMF divided by 32";
                break;
        }

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Drive::OCPThreshold& voltage)
    {
        switch (voltage)
        {
            case drivers::stepper_motor::Drv8711Sync::Drive::OCPThreshold::_250mV:
                stream << "250";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::OCPThreshold::_500mV:
                stream << "500";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::OCPThreshold::_750mV:
                stream << "750";
                break;
            default:
                stream << "1000";
                break;
        }

        stream << " mV";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Drive::OCPDeglitchTime time)
    {
        switch (time)
        {
            case drivers::stepper_motor::Drv8711Sync::Drive::OCPDeglitchTime::_1us:
                stream << "1";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::OCPDeglitchTime::_2us:
                stream << "2";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::OCPDeglitchTime::_4us:
                stream << "4";
                break;
            default:
                stream << "8";
                break;
        }

        stream << " us";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Drive::GateDriveTime time)
    {
        switch (time)
        {
            case drivers::stepper_motor::Drv8711Sync::Drive::GateDriveTime::_250ns:
                stream << "250";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::GateDriveTime::_500ns:
                stream << "500";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::GateDriveTime::_1000ns:
                stream << "1000";
                break;
            default:
                stream << "2000";
                break;
        }

        stream << " ns";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Drive::LowSideGateDrivePeakCurrent current)
    {
        switch (current)
        {
            case drivers::stepper_motor::Drv8711Sync::Drive::LowSideGateDrivePeakCurrent::_100mA:
                stream << "100";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::LowSideGateDrivePeakCurrent::_200mA:
                stream << "200";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::LowSideGateDrivePeakCurrent::_300mA:
                stream << "300";
                break;
            default:
                stream << "400";
                break;
        }

        stream << " mA";

        return stream;
    }

    infra::TextOutputStream& operator<<(infra::TextOutputStream& stream, const drivers::stepper_motor::Drv8711Sync::Drive::HighSideGateDrivePeakCurrent current)
    {
        switch (current)
        {
            case drivers::stepper_motor::Drv8711Sync::Drive::HighSideGateDrivePeakCurrent::_50mA:
                stream << "50";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::HighSideGateDrivePeakCurrent::_100mA:
                stream << "100";
                break;
            case drivers::stepper_motor::Drv8711Sync::Drive::HighSideGateDrivePeakCurrent::_150mA:
                stream << "150";
                break;
            default:
                stream << "200";
                break;
        }

        stream << " mA";

        return stream;
    }
}

namespace application::parsers
{
    Drv8711::Drv8711(infra::BoundedConstString name, infra::BoundedConstString description, services::TerminalWithCommands& terminal, services::Tracer& tracer, drivers::stepper_motor::Drv8711Sync& drv8711)
        : services::TerminalCommandsAndMenu(terminal)
        , menu(name, description, *this)
        , terminal(terminal)
        , tracer(tracer)
        , drv8711(drv8711)
    {}

    infra::MemoryRange<const services::TerminalCommands::Command> Drv8711::Commands()
    {
        //clang-format off
        static const std::array<Command, 8> commands = { {
            { { "rc", "read_control", "Read register control" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadControl();
                } },
            { { "rt", "read_torque", "Read register torque" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadTorque();
                } },
            { { "ro", "read_off", "Read register off" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadOff();
                } },
            { { "rb", "read_blank", "Read register blank" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadBlank();
                } },
            { { "rdc", "read_decay", "Read register decay" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadDecay();
                } },
            { { "rsl", "read_stall", "Read register stall" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadStall();
                } },
            { { "rdr", "read_drive", "Read register drive" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadDrive();
                } },
            { { "rst", "read_status", "Read register status" }, [this]([[maybe_unused]] const infra::BoundedConstString& params)
                {
                    this->ReadStatus();
                } },
        } };
        //clang-format on

        return infra::MakeRange(commands);
    }

    services::TerminalCommandsAndMenu::MenuInfo& Drv8711::Menu()
    {
        return menu;
    }

    void Drv8711::ReadControl()
    {
        drv8711.GetControlRegister([this](const drivers::stepper_motor::Drv8711Sync::Control& reg)
            {
                this->tracer.Trace() << "Register Control";
                this->tracer.Trace() << "\tEnable           : " << reg.enableMotor;
                this->tracer.Trace() << "\tDirection        : " << reg.direction;
                this->tracer.Trace() << "\tSteps            : " << reg.step;
                this->tracer.Trace() << "\tStall detection  : " << reg.stallDetection;
                this->tracer.Trace() << "\tAmplifier gain   : " << reg.amplifierGain;
                this->tracer.Trace() << "\tDead time        : " << reg.deadTime;
                this->tracer.Trace() << "\r\n";
            });
    }

    void Drv8711::ReadTorque()
    {
        drv8711.GetTorqueRegister([this](const drivers::stepper_motor::Drv8711Sync::Torque& reg)
            {
                this->tracer.Trace() << "Register Torque";
                this->tracer.Trace() << "\tBack EMF Sample Threshold : " << reg.backEMFSampleThreshold;
                this->tracer.Trace() << "\tTorque                    : " << reg.fullScaleCurrent;
                this->tracer.Trace() << "\r\n";
            });
    }

    void Drv8711::ReadOff()
    {
        drv8711.GetOffTimeRegister([this](const drivers::stepper_motor::Drv8711Sync::Off& reg)
            {
                this->tracer.Trace() << "Register Off";
                this->tracer.Trace() << "\tPWM mode       : " << reg.pwmMode;
                this->tracer.Trace() << "\tFixed off time : " << reg.FixedOffTimeInNanoSeconds() << " ns";
                this->tracer.Trace() << "\r\n";
            });
    }

    void Drv8711::ReadBlank()
    {
        drv8711.GetBlankRegister([this](const drivers::stepper_motor::Drv8711Sync::Blank& reg)
            {
                this->tracer.Trace() << "Register Blank";
                this->tracer.Trace() << "\tAdaptive blank time enabled? : " << reg.adaptativeBlankingTime;
                this->tracer.Trace() << "\tCurrent trip blanking time   : " << reg.BlankingTimeInNanoSeconds() << " ns";
                this->tracer.Trace() << "\r\n";
            });
    }

    void Drv8711::ReadDecay()
    {
        drv8711.GetDecayRegister([this](const drivers::stepper_motor::Drv8711Sync::Decay& reg)
            {
                this->tracer.Trace() << "Register Decay";
                this->tracer.Trace() << "\tDecay mode                   : " << reg.mode;
                this->tracer.Trace() << "\tMixed decay transition time  : " << reg.DecayTransitionTimeInNanoSeconds() << " ns";
                this->tracer.Trace() << "\r\n";
            });
    }

    void Drv8711::ReadStall()
    {
        drv8711.GetStallRegister([this](const drivers::stepper_motor::Drv8711Sync::Stall& reg)
            {
                this->tracer.Trace() << "Register Stall";
                this->tracer.Trace() << "\tStall detect threshold : " << reg.detectionThreshold;
                this->tracer.Trace() << "\tStall assertion        : " << reg.assertCounter;
                this->tracer.Trace() << "\tBack EMF division      : 0x" << infra::hex << reg.backEMFDivisor;
                this->tracer.Trace() << "\r\n";
            });
    }

    void Drv8711::ReadDrive()
    {
        drv8711.GetDriveRegister([this](const drivers::stepper_motor::Drv8711Sync::Drive reg)
            {
                this->tracer.Trace() << "Register Drive";
                this->tracer.Trace() << "\tOCP threshold                    : " << reg.oCPThreshold;
                this->tracer.Trace() << "\tOCP deglitch time                : " << reg.oCPDeglitchTime;
                this->tracer.Trace() << "\tLow side gate drive time         : " << reg.lowSideGateDriveTime;
                this->tracer.Trace() << "\tHigh side gate drive time        : " << reg.highSideGateDriveTime;
                this->tracer.Trace() << "\tLow side gate drive peak current : " << reg.lowSideGateDrivePeakCurrent;
                this->tracer.Trace() << "\tHigh side gate drive peak current: " << reg.highSideGateDrivePeakCurrent;
                this->tracer.Trace() << "\r\n";
            });
    }

    void Drv8711::ReadStatus()
    {
        drv8711.GetStatusRegister([this](const drivers::stepper_motor::Drv8711Sync::Status reg)
            {
                this->tracer.Trace() << "Register Status";
                this->tracer.Trace() << "\tOvertemperature      : " << reg.overTemperatureShutdown;
                this->tracer.Trace() << "\tChannel A overcurrent: " << reg.channelAOverCurrentShutdown;
                this->tracer.Trace() << "\tChannel B overcurrent: " << reg.channelBOverCurrentShutdown;
                this->tracer.Trace() << "\tChannel A predriver  : " << reg.channelAPreDriveFault;
                this->tracer.Trace() << "\tChannel B predriver  : " << reg.channelBPreDriveFault;
                this->tracer.Trace() << "\tUndervoltage         : " << reg.underVoltageLockout;
                this->tracer.Trace() << "\tStall detected       : " << reg.stallDetected;
                this->tracer.Trace() << "\r\n";
            });
    }
}
