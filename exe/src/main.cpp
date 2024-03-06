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
//    std::unique_ptr<DIContainer> container = GlobalDI::builder()
//            .register_singleton<PostgreSQLDatabase, IDatabase>()
//            .register_singleton<FileLogger, ILogger>()
//            .register_singleton<UserController>()
//            .register_singleton<TaskController>()
//            .register_transient<UserModel>()
//            .register_transient<TaskModel>()
//            .build();
    std::unique_ptr<DIContainer> container = GlobalDI::builder().build();
    std::cout << "HERE" << std::endl;
    Application& app = container->resolve<Application>();
    app.run();

    return EXIT_SUCCESS;
}