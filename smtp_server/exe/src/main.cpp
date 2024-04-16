#include "classic_di/DIContainerBuilder.hpp"
#include "classic_di/DIContainer.hpp"
#include "../../database/include/database/command/IDBCommand.hpp"
#include "../../database/include/database/command/user/CreateUserCommand.hpp"
#include "../../database/include/database/command/user/DeleteUserCommand.hpp"

using namespace Database;
using namespace Database::Command;

class Dummy
{
public:
    void dodo() const
    {
        std::cout << "dodo" << std::endl;
    }

    static Dummy create()
    {
        return {};
    }
};

class CommandUser
{
public:
    explicit CommandUser(IDBCommand& command, const Dummy& dummy)
        : command_ { command }
        , dummy_ { dummy }
    {}

public:
    static CommandUser create(IDBCommand& command, Dummy& dummy)
    {
        return CommandUser { command, dummy };
    }

    void use_command()
    {
        IDBCommand::ParamsType create_params = {
            { "name", "Ruslan" },
            { "password", "12345" },
            { "email", "non-linear@ukr.net"}
        };
        command_.execute(create_params);
        dummy_.dodo();
    }

private:
    IDBCommand& command_;
    const Dummy& dummy_;
};

int main()
{

//    DIContainer container = DIContainerBuilder{}
//        .register_transient<User::CreateUserCommand>()
//            .as_interface<IDBCommand>()
//            .with_tag("create-user")
//            .done()
//        .register_transient<User::DeleteUserCommand>()
//            .as_interface<IDBCommand>()
//            .with_tag("delete-user")
//            .done()
//        .register_singleton<CommandUser>()
//            .with_dependency_tag<IDBCommand>("create-user")
//            .done()
//        .build();

    auto builder = DIContainerBuilder{};
    builder.register_transient<User::CreateUserCommand>()
            .as_interface<IDBCommand>()
            .with_tag("create-user")
            .done()
            .register_transient<User::DeleteUserCommand>()
            .as_interface<IDBCommand>()
            .with_tag("delete-user")
            .done()
            .register_singleton<CommandUser>()
            .with_dependency_tag<IDBCommand>("create-user")
            .done()
            .register_singleton<Dummy>()
            .done();

    DIContainer container = builder.build();

    {
        IDBCommand& create_user_command = container.resolve<IDBCommand>("create-user");
        IDBCommand::ParamsType create_params = {
            { "name", "Ruslan" },
            { "password", "12345" },
            { "email", "non-linear@ukr.net"}
        };
        create_user_command.execute(create_params);
    }

    {
        IDBCommand& delete_user_command = container.resolve<IDBCommand>("delete-user");
        IDBCommand::ParamsType delete_params = { { "name", "Ruslan" } };
        delete_user_command.execute(delete_params);
    }

    {
        CommandUser& command_user = container.resolve<CommandUser>();
        command_user.use_command();
    }

    return EXIT_SUCCESS;
}