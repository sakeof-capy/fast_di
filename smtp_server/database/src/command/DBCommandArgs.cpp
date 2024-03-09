#include "../../include/database/command/DBCommandArgs.hpp"

namespace Database::Command
{

DBCommandArgs::DBCommandArgs(std::initializer_list<ValueType> initializer_list)
    : container_ { initializer_list }
{}

auto DBCommandArgs::operator[](const KeyArgType& key) -> ValueArgType&
{
    return container_[key];
}

auto DBCommandArgs::at(const KeyArgType& key) -> ValueArgType&
{
    return container_.at(key);
}

auto DBCommandArgs::at(const KeyArgType& key) const -> const ValueArgType&
{
    return container_.at(key);
}

auto DBCommandArgs::contains(const KeyArgType& key) const -> bool
{
    return container_.contains(key);
}

}
