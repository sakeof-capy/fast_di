#ifndef FAST_DI_LIBS_DB_COMMAND_ARGS_HPP
#define FAST_DI_LIBS_DB_COMMAND_ARGS_HPP

#pragma once

#include <string>
#include <map>

namespace Database::Command
{

class DBCommandArgs
{
public:
    using KeyArgType = std::string;
    using ValueArgType = std::string;

private:
    using ArgsContainer = std::map<KeyArgType, ValueArgType>;

public:
    using ValueType = typename ArgsContainer::value_type;

public:
    DBCommandArgs(std::initializer_list<ValueType> initializer_list);

public:
    ValueArgType& operator[](const KeyArgType& key);
    ValueArgType& at(const KeyArgType& key);
    const ValueArgType& at(const KeyArgType& key) const;
    bool contains(const KeyArgType& key) const;

private:
    ArgsContainer container_;
};

}

#endif //FAST_DI_LIBS_DB_COMMAND_ARGS_HPP
