#include "../../../include/command/user/CreateUserCommand.hpp"
#include <iostream>

namespace Database::Command::User
{

using ResultType = IDBCommand::ResultType;

std::optional<ResultType> CreateUserCommand::execute(const ParamsType& params)
{
    try
    {
        KeyParamType name = params.at("name");
        KeyParamType password = params.at("password");
        std::cout << "User created WITH name = " << name << ", password = " << password << '\n';
    }
    catch(...)
    {
        std::cout << "Incorrect Params. Command CreateUserCommand not executed.\n";
    }

    return std::nullopt;
}

}
