#include "classic_di/GlobalDI.hpp"
#include "../include/exe/DI.hpp"
#include "../include/exe/Application.hpp"
#include <stdlib.h>

int main()
{
    subscribe_all_dependencies();
    std::unique_ptr<DIContainer> container = GlobalDI::build_container();

    Application_& app = container->resolve<Application_>();
    app.run();

    return EXIT_SUCCESS;
}


//    std::unique_ptr<DIContainer> container = GlobalDI::builder()
//            .register_singleton<PostgreSQLDatabase, IDatabase>()
//            .register_singleton<FileLogger, ILogger>()
//            .register_singleton<UserController>()
//            .register_singleton<TaskController>()
//            .register_transient<UserModel>()
//            .register_transient<TaskModel>()
//            .build();
//    std::unique_ptr<DIContainer> container = GlobalDI::builder().build();
//    Application& app = container->resolve<Application>();
//    app.run();