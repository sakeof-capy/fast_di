#include <iostream>
#include "classic_di/DIContainerBuilder.hpp"

#include "../include/exe/Application.h"

int main()
{
    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
            .register_singleton<PostgreSQLDatabase>()
            .register_singleton<FileLogger>()
            .register_singleton<UserController>()
            .register_singleton<TaskController>()
            .register_transient<UserModel>()
            .register_transient<TaskModel>()
            .register_singleton<Application>()
            .build();

    Application& app = container->resolve<Application>();
    app.run();

    return EXIT_SUCCESS;
}