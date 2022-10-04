#ifndef MEYERS_SINGLETON_HPP_
#define MEYERS_SINGLETON_HPP_

namespace Meyers
{
    // singleton Meyersa
    template <typename T>
    class SingletonHolder
    {
    public:
        SingletonHolder(const SingletonHolder&) = delete;
        SingletonHolder& operator=(const SingletonHolder&) = delete;

        static T& instance()
        {
            static T unique_instance;

            return unique_instance;
        }

    private:
        SingletonHolder() = default;
    };
}
#endif /* MEYERS_SINGLETON_HPP_ */
