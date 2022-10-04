#ifndef PHOENIX_SINGLETON_HPP_
#define PHOENIX_SINGLETON_HPP_

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace Phoenix
{
    template <typename T>
    class SingletonHolder
    {
    public:
        SingletonHolder(const SingletonHolder&) = delete;
        SingletonHolder& operator=(const SingletonHolder&) = delete;

        static T& instance()
        {
            if (!instance_)
            {
                if (destroyed_)
                    on_dead_reference();
                else
                    create();
            }
            return *instance_;
        }

    private:
        static void create()
        {
            alignas(T) static char static_memory_[sizeof(T)];

            instance_ = new (&static_memory_) T;
            std::atexit(&destroy);
        }

        static void destroy()
        {
            instance_->~T();
            destroyed_ = true;
            instance_ = 0;
        }

        static void on_dead_reference()
        {
            std::cout << "Dead reference encountered..." << std::endl;
            std::cout << "Creating a phoenix object..." << std::endl;
            create();
            destroyed_ = false;
        }

    private:
        SingletonHolder() = default;

        static T* instance_;
        static bool destroyed_;
    };

    template <typename T>
    T* SingletonHolder<T>::instance_ = nullptr;

    template <typename T>
    bool SingletonHolder<T>::destroyed_ = false;
}
#endif /* PHOENIX_SINGLETON_HPP_ */
