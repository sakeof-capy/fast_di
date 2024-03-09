#include "../../../include/database/command/user/CreateUserCommand.hpp"
#include <iostream>

namespace Database::Command::User
{

auto CreateUserCommand::execute(const ParamsType& params) -> std::optional<ResultType>
{
    try
    {
        KeyArgType name = params.at("name");
        KeyArgType password = params.at("password");
        std::cout << "User created WITH name = " << name << ", password = " << password << '\n';
    }
    catch(...)
    {
        std::cout << "Incorrect Params. Command CreateUserCommand not executed.\n";
    }

    return std::nullopt;
}

}
