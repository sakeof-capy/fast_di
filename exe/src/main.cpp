#include "classic_di/DIContainerBuilder.hpp"
#include "classic_di/type_traits/TypeLists.hpp"
#include "classic_di/type_traits/FunctionTypeTraits.hpp"
#include "../include/exe/Application.hpp"
#include "../include/exe/Database/PostgreSQLDatabase.hpp"
#include "../include/exe/Logger/FileLogger.hpp"
#include "../include/exe/Models/UserModel.hpp"

#include "classic_di/DISubscribe.hpp"

int main()
{
//    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
//            .register_singleton<PostgreSQLDatabase, IDatabase>()
//            .register_singleton<FileLogger, ILogger>()
//            .register_singleton<UserController>()
//            .register_singleton<TaskController>()
//            .register_transient<UserModel>()
//            .register_transient<TaskModel>()
//            .register_singleton<Application, Application>()
//            .build();

    std::unique_ptr<DIContainer> container = GlobalDI::builder()
//            .register_singleton<PostgreSQLDatabase, IDatabase>()
//            .register_singleton<FileLogger, ILogger>()
//            .register_singleton<UserController>()
//            .register_singleton<TaskController>()
//            .register_transient<UserModel>()
//            .register_transient<TaskModel>()
            .build();
//    using Udd = UserModel;
//    auto a = Udd{};
    Application& app = container->resolve<Application>();
    app.run();

    return EXIT_SUCCESS;
}