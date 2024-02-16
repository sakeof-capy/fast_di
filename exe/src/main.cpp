#include <iostream>
#include "classic_di/DIContainerBuilder.hpp"

#include "../include/exe/Application.h"

class Dependency
{
public:
    static Dependency create()
    {
        return Dependency{};
    }
public:
    int x = 0;
};

class App
{
public:
    explicit App(Dependency& dependency) : dependency_ { dependency } {}

public:
    static App create(Dependency& dependency)
    {
        return App { dependency };
    }

private:
    Dependency& dependency_;
};


int main()
{
//    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
//            .register_singleton<PostgreSQLDatabase>()
//            .register_singleton<FileLogger>()
//            .register_singleton<UserController>()
//            .register_singleton<TaskController>()
//            .register_transient<UserModel>()
//            .register_transient<TaskModel>()
//            .register_singleton<Application>()
//            .build();

    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
            .register_singleton<App>()
            .register_singleton<Dependency>()
            .build();

    Application& app = container->resolve<Application>();
    app.run();

    return EXIT_SUCCESS;
}