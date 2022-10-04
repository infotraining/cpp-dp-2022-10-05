#ifndef MULTITHREADING_SINGLETON_HPP
#define MULTITHREADING_SINGLETON_HPP

#include <memory>
#include <mutex>

namespace Multithreading
{
    template <typename T>
    class SingletonHolder
    {
    private:
        SingletonHolder() = default;
        static std::unique_ptr<T> instance_;
        static std::once_flag init_flag_;

    public:
        SingletonHolder(const SingletonHolder&) = delete;
        SingletonHolder<T>& operator=(const SingletonHolder&) = delete;

        static T& instance()
        {
            std::call_once(init_flag_, [] { instance_.reset(new T()); });
            return *instance_;
        }
    };

    template <typename T>
    std::unique_ptr<T> SingletonHolder<T>::instance_;

    template <typename T>
    std::once_flag SingletonHolder<T>::init_flag_;
}

#endif
