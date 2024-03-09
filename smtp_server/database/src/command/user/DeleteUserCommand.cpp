#include "../../../include/command/user/DeleteUserCommand.hpp"
#include <iostream>

namespace Database::Command::User
{

using ResultType = IDBCommand::ResultType;
using ParamsType = IDBCommand::ParamsType;

std::optional<ResultType> DeleteUserCommand::execute(const ParamsType& params)
{
    try
    {
        KeyParamType name = params.at("name");
        std::cout << "User deleted WITH name = " << name << '\n';
    }
    catch(...)
    {
        std::cout << "Incorrect Params. Command DeleteUserCommand not executed.\n";
    }

    return std::nullopt;
}

}
