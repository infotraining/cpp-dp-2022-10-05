#include "mediator.hpp"

using namespace std;

int main()
{
    // Colleagues
    TemperatureMonitor temp_monitor{20.5};
    Fan fan;
    ToggleButton btn_fan("Fan state");
    LineEdit temp_display{"Current temperature"};

    // Mediator
    TemperatureMediator mediator{temp_monitor, fan, btn_fan, &temp_display};

    temp_monitor.set_temperature(22.0);
    temp_monitor.set_temperature(23.0);
    temp_monitor.set_temperature(24.0);
    temp_monitor.set_temperature(25.0);
    btn_fan.toggle();
    temp_monitor.set_temperature(24.0);
    temp_monitor.set_temperature(23.0);
    temp_monitor.set_temperature(22.0);
    btn_fan.toggle();
    temp_monitor.set_temperature(23.0);
    temp_monitor.set_temperature(24.0);
    temp_monitor.set_temperature(25.0);
    btn_fan.toggle();
}
