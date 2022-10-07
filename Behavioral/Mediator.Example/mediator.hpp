#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include "observer.hpp"
#include <iostream>
#include <string>

// Colleague1
class TemperatureMonitor : public Observable<TemperatureMonitor, double>
{
private:
    double current_temperature_;

public:
    TemperatureMonitor(double temp)
        : current_temperature_{temp}
    {
    }

    void set_temperature(double new_temperature)
    {
        if (current_temperature_ != new_temperature)
        {
            current_temperature_ = new_temperature;

            // sending notification to all observers
            notify(*this, current_temperature_);
        }
    }

    double current_temperature() const
    {
        return current_temperature_;
    }
};

//Colleague2
class Fan
{
    bool is_on_ = false;

public:
    void on()
    {
        is_on_ = true;
        std::cout << "Fan is on...\n";
    }

    void off()
    {
        is_on_ = false;
        std::cout << "Fan is off...\n";
    }

    bool is_on() const
    {
        return is_on_;
    }
};

//Colleague3
class LineEdit
{
    std::string caption_;
    std::string value_;

public:
    explicit LineEdit(std::string caption, std::string value = "")
        : caption_{std::move(caption)}
        , value_{std::move(value)}
    {
    }

    void set_value(std::string new_value)
    {
        value_ = new_value;
    }

    const std::string& value() const
    {
        return value_;
    }

    void refresh() const
    {
        std::cout << caption_ << ": " << value_ << std::endl;
    }
};

// colleague4
class ToggleButton : public Observable<ToggleButton, bool>
{
    bool is_on_;
    std::string caption_;

public:
    explicit ToggleButton(std::string caption)
        : is_on_{false}
        , caption_{std::move(caption)}
    {
    }

    bool toggle()
    {
        std::cout << caption_ << " clicked...\n";
        is_on_ = !is_on_;
        notify(*this, is_on_);

        return is_on_;
    }

    void refresh() const
    {
        std::cout << caption_ << ": " << std::boolalpha << is_on_ << std::endl;
    }
};

// Mediator
class TemperatureMediator : public Observer<TemperatureMonitor, double>, public Observer<ToggleButton, bool>
{
    TemperatureMonitor& temperature_monitor_;
    Fan& fan_;
    ToggleButton& btn_fan_on_off_;
    LineEdit* temperature_display_;

public:
    TemperatureMediator(TemperatureMonitor& temp_monitor, Fan& fan, ToggleButton& btn_fan_on_off, LineEdit* temp_display = nullptr)
        : temperature_monitor_{temp_monitor}
        , fan_{fan}
        , btn_fan_on_off_{btn_fan_on_off}
        , temperature_display_{temp_display}
    {
        // register mediator as observers for events
        temperature_monitor_.subscribe(this);
        btn_fan_on_off_.subscribe(this);

        if (temperature_display_)
            temperature_display_->set_value(std::to_string(temp_monitor.current_temperature()));
    }

    void update(TemperatureMonitor& temp_monitor, double temp) override
    {
        std::cout << "Mediator notified about temperature changed...\n";
        if (temperature_display_)
        {
            temperature_display_->set_value(std::to_string(temp));
            temperature_display_->refresh();
        }
    }

    void update(ToggleButton& btn, bool state) override
    {
        if (state)
            fan_.on();
        else
            fan_.off();
    }
};

#endif /*MEDIATOR_HPP_*/
