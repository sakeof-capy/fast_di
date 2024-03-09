#include "classic_di/DIContainerBuilder.hpp"
#include "classic_di/DIContainer.hpp"
#include "../../database/include/command/IDBCommand.hpp"
#include "../../database/include/command/user/CreateUserCommand.hpp"
#include "../../database/include/command/user/DeleteUserCommand.hpp"

using namespace Database::Command;

int main()
{
    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
        .register_singleton<User::CreateUserCommand, IDBCommand>("create-user")
        .register_singleton<User::DeleteUserCommand, IDBCommand>("delete-user")
        .build();

    {
        IDBCommand& create_user_command = container->resolve<IDBCommand>("create-user");
        IDBCommand::ParamsType create_params = { { "name", "Ruslan"}, {"password", "12345"}};
        create_user_command.execute(create_params);
    }

    {
        IDBCommand& delete_user_command = container->resolve<IDBCommand>("delete-user");
        IDBCommand::ParamsType delete_params = { { "name", "Ruslan"}};
        delete_user_command.execute(delete_params);
    }

    return EXIT_SUCCESS;
}