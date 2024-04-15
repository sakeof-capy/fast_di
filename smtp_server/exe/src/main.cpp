#include "classic_di/DIContainerBuilder.hpp"
#include "classic_di/DIContainer.hpp"
#include "../../database/include/database/command/IDBCommand.hpp"
#include "../../database/include/database/command/user/CreateUserCommand.hpp"
#include "../../database/include/database/command/user/DeleteUserCommand.hpp"

using namespace Database;
using namespace Database::Command;

int main()
{
    DIContainerBuilder builder{};
    builder.register_singleton<User::CreateUserCommand>()
                .as_interface<IDBCommand>()
                .with_tag("create-user")
                .done()
           .register_singleton<User::DeleteUserCommand>()
                .as_interface<IDBCommand>()
                .with_tag("delete-user")
                .done();

    std::unique_ptr<DIContainer> container = builder.build();
//    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
//        //.register_singleton<Connection::PQXXConnectionHandler, Connection::ISQLConnectionHandler>()
//        .register_singleton<User::CreateUserCommand, IDBCommand>("create-user")
//        .register_singleton<User::DeleteUserCommand, IDBCommand>("delete-user")
//        .build();

    {
        IDBCommand& create_user_command = container->resolve<IDBCommand>("create-user");
        IDBCommand::ParamsType create_params = { { "name", "Ruslan" }, { "password", "12345" }, { "email", "non-linear@ukr.net"} };
        create_user_command.execute(create_params);
    }

    {
        IDBCommand& delete_user_command = container->resolve<IDBCommand>("delete-user");
        IDBCommand::ParamsType delete_params = { { "name", "Ruslan" } };
        delete_user_command.execute(delete_params);
    }

    return EXIT_SUCCESS;
}