#include <string>

#include "devices.hpp"
#include "meyers_singleton.hpp"
#include "phoenix_singleton.hpp"
#include "simple_singleton.hpp"

int main()
{
    try
    {
        char c = 'a';
        KeyboardDevice::instance().on_key_pressed(c);
        c = '@';
        KeyboardDevice::instance().on_key_pressed(c);
    }
    catch (const std::exception& e)
    {
        std::cout << std::string("Exception: ") + e.what() << std::endl;
    }
}