#ifndef DI_CONTAINERS_CREATEUSERCOMMAND_HPP
#define DI_CONTAINERS_CREATEUSERCOMMAND_HPP

#include "../IDBCommand.hpp"

namespace Database::Command::User
{

class CreateUserCommand : public IDBCommand
{
public:
    ~CreateUserCommand() override = default;

    static CreateUserCommand create() { return {}; }

public:
    std::optional<ResultType> execute(const ParamsType& params) override;
};

}

//MakeInjectableAs(CreateUserCommand_) Entity(Database::Command::User::CreateUserCommand)
//                                     With <
//        SingletonAsInterface(CreateUserCommand_, Database::Command::IDBCommand) ConstructedWith <> Injected
//> AsInjectionRulesFor(CreateUserCommand_)


#endif //DI_CONTAINERS_CREATEUSERCOMMAND_HPP
