#include "../../../include/database/command/user/DeleteUserCommand.hpp"
#include <iostream>

namespace Database::Command::User
{

auto DeleteUserCommand::execute(const ParamsType& params) -> std::optional<ResultType>
{
    try
    {
        KeyArgType name = params.at("name");
        std::cout << "User deleted WITH name = " << name << '\n';
    }
    catch(...)
    {
        std::cout << "Incorrect Params. Command DeleteUserCommand not executed.\n";
    }

    return std::nullopt;
}

}
