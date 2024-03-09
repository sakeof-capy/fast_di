#ifndef DI_CONTAINERS_DELETEUSERCOMMAND_HPP
#define DI_CONTAINERS_DELETEUSERCOMMAND_HPP

#include "database/command/IDBCommand.hpp"

namespace Database::Command::User
{

class DeleteUserCommand : public IDBCommand
{
public:
    ~DeleteUserCommand() override = default;

    static DeleteUserCommand create() { return {}; }

public:
    std::optional<ResultType> execute(const ParamsType& params) override;
};

}

#endif //DI_CONTAINERS_DELETEUSERCOMMAND_HPP
