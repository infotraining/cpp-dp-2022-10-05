#ifndef GENERIC_FACTORY_HPP
#define GENERIC_FACTORY_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

template <typename ProductType, typename TypeId = std::string, typename CreatorType = std::function<std::unique_ptr<ProductType>()> >
class GenericFactory
{
    std::unordered_map<TypeId, CreatorType> creators_;
public:
    bool register_creator(TypeId id, CreatorType creator)
    {
        typename std::unordered_map<TypeId, CreatorType>::iterator it;
        bool is_inserted;

        tie(it, is_inserted) = creators_.insert(make_pair(move(id), move(creator)));

        return is_inserted;
    }

    std::unique_ptr<ProductType> create(const TypeId& id)
    {
        auto& creator = creators_.at(id);

        return creator();
    }
};

#endif // GENERIC_FACTORY_HPP
