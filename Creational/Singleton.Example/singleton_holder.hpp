#ifndef SINGLETON_HOLDER_HPP_
#define SINGLETON_HOLDER_HPP_

#include <atomic>
#include <cassert>
#include <mutex>

namespace GenericSingleton
{

    typedef void (*atexit_pfn_t)();

    /////////////////////////////////////////////////////////////////////////
    // klasa szablonowa CreateUsingNew
    // implementacja wytycznej CreationPolicy używanej przez SingletonHolder
    /////////////////////////////////////////////////////////////////////////

    template <typename T>
    struct CreateUsingNew
    {
        static T* create()
        {
            return new T;
        }

        static void destroy(T* p)
        {
            delete p;
        }
    };

    /////////////////////////////////////////////////////////////////////////
    // klasa CreateStatic
    // implementacja wytycznej CreationPolicy używanej przez SingletonHolder
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct CreateStatic
    {
        static T* create()
        {
            alignas(T) static char static_memory[sizeof(T)];
            return new (&static_memory) T;
        }

        static void destroy(T* p)
        {
            p->~T();
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // klasa szablonowa DefaultLifetime
    // implementacja wytycznej LifetimePolicy używanej przez SingletonHolder
    ////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct DefaultLifetime
    {
        static void schedule_destruction(T*, atexit_pfn_t pFun)
        {
            std::atexit(pFun);
        }

        static void on_dead_reference()
        {
            throw std::logic_error("Dead Reference Detected");
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // klasa szablonowa PhoenixSingleton
    // implementacja wytycznej LifetimePolicy używanej przez SingletonHolder
    ////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    class PhoenixSingleton
    {
    public:
        static void schedule_destruction(T*, atexit_pfn_t pFun)
        {
            std::atexit(pFun);
        }

        static void on_dead_reference()
        {
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // klasa szablonowa NoDestroySingleton
    // implementacja wytycznej LifetimePolicy używanej przez SingletonHolder
    ////////////////////////////////////////////////////////////////////////////////
    template <class T>
    struct NoDestroy
    {
        static void schedule_destruction(T*, atexit_pfn_t pFun)
        {
        }

        static void on_dead_reference()
        {
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // klasa szablonowa SingleThreaded
    // implementacja wytycznej ThreadedPolicy używanej przez SingletonHolder
    ////////////////////////////////////////////////////////////////////////////////
    template <class T>
    struct SingleThreaded
    {
        using InstancePtr = T*;

        struct Mutex
        {
        };

        struct Lock
        {
            Lock(Mutex& mtx){};
        };
    };

    ////////////////////////////////////////////////////////////////////////////////
    // klasa szablonowa MultiThreaded
    // implementacja wytycznej ThreadedPolicy używanej przez SingletonHolder
    ////////////////////////////////////////////////////////////////////////////////
    template <class T>
    struct MultiThreaded
    {
        using InstancePtr = std::atomic<T*>;

        using Mutex = std::mutex;

        using Lock = std::lock_guard<Mutex>;
    };

    ////////////////////////////////////////////////////////////////////////////////
    // klasa szablonowa SingletonHolder
    ////////////////////////////////////////////////////////////////////////////////
    template <
        typename T,
        template <typename> class CreationPolicy = CreateUsingNew,
        template <typename> class LifetimePolicy = DefaultLifetime,
        template <typename> class ThreadedPolicy = SingleThreaded>
    class SingletonHolder
    {
    public:
        SingletonHolder(const SingletonHolder&) = delete;
        SingletonHolder& operator=(const SingletonHolder&) = delete;
        static T& instance();

    private:
        static void make_instance();
        static void destroy_singleton();

        static typename ThreadedPolicy<T>::Mutex mutex_;
        static typename ThreadedPolicy<T>::InstancePtr instance_;
        static bool destroyed_;

        // prywatny konstruktor
        SingletonHolder() = default;
    };

    // dane statyczne singletonu
    template <class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class> class ThreadedPolicy>
    typename ThreadedPolicy<T>::Mutex SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadedPolicy>::mutex_;

    template <class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class> class ThreadedPolicy>
    typename ThreadedPolicy<T>::InstancePtr SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadedPolicy>::instance_{nullptr};

    template <class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class> class ThreadedPolicy>
    bool SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadedPolicy>::destroyed_;

    // implementacja metody SingletonHolder::instance()
    template <class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class> class ThreadedPolicy>
    inline T& SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadedPolicy>::instance()
    {
        if (!instance_)
        {
            typename ThreadedPolicy<T>::Lock lock{mutex_};

            if (!instance_)
            {
                if (destroyed_)
                {
                    LifetimePolicy<T>::on_dead_reference();
                    destroyed_ = false;
                }

                instance_ = CreationPolicy<T>::create();
                LifetimePolicy<T>::schedule_destruction(instance_, &destroy_singleton);
            }
        }

        return *instance_;
    }

    // implementacja metody SingletonHolder::destroy_singleton()
    template <class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class> class ThreadedPolicy>
    void SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadedPolicy>::destroy_singleton()
    {
        assert(!destroyed_);
        CreationPolicy<T>::destroy(instance_);
        destroyed_ = true;
        instance_ = nullptr;
    }
}

#endif /* SINGLETON_HOLDER_HPP_ */
