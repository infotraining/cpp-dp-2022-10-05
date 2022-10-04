#ifndef DEVICES_HPP_
#define DEVICES_HPP_

#include <stdexcept>

#include "meyers_singleton.hpp"
#include "multithreading_singleton.hpp"
#include "phoenix_singleton.hpp"
#include "simple_singleton.hpp"
#include "singleton_holder.hpp"

namespace Impl = Simple;

class Log
{
public:
    Log()
    {
        std::cout << "Log()" << std::endl;
    }

    ~Log()
    {
        std::cout << "~Log()" << std::endl;
    }

    void save(const std::string& msg) const
    {
        std::cout << "Logging: " << msg << std::endl;
    }
};

using Logger = Impl::SingletonHolder<Log>;

void may_throw()
{
    throw std::runtime_error("Runtime error during closing a Keyboard");
}

class Keyboard
{
public:
    Keyboard()
    {
        std::cout << "Keyboard()" << std::endl;
    }

    ~Keyboard()
    {
        std::cout << "~Keyboard()" << std::endl;
        try
        {
            may_throw();
        }
        catch (...)
        {
            Logger::instance().save("Problem with Keyboard's destructor");
        }
    }

    void on_key_pressed(char c)
    {
        std::cout << "Key '" << c << "' was pressed... " << std::endl;

        if (c == '@')
        {
            Logger::instance().save("Problem with on_key_pressed function...");
            throw std::runtime_error("Runtime error during on_key_pressed...");
        }
    }
};

using KeyboardDevice = Impl::SingletonHolder<Keyboard>;

#endif /* DEVICES_HPP_ */
