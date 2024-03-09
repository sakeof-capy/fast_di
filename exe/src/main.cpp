#include "classic_di/DIContainerBuilder.hpp"
#include "classic_di/type_traits/TypeLists.hpp"
#include "classic_di/type_traits/FunctionTypeTraits.hpp"
#include "../include/exe/Application.hpp"
#include "../include/exe/Database/PostgreSQLDatabase.hpp"
#include "../include/exe/Logger/FileLogger.hpp"
#include "../include/exe/Models/UserModel.hpp"

#include "classic_di/DISubscribe.hpp"

class SomeI
{
public:
    virtual ~SomeI() = default;
    virtual void do_smth() = 0;
};

class Impl1 : public SomeI
{
public:
    static Impl1 create() { return {}; }
    void do_smth() { std::cout << "first" << std::endl; }
};

class Impl2 : public SomeI
{
public:
    static Impl2 create() { return {}; }
    void do_smth() { std::cout << "second" << std::endl; }
};

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
//    std::unique_ptr<DIContainer> container = GlobalDI::builder().build();
//    Application& app = container->resolve<Application>();
//    app.run();

    std::unique_ptr<DIContainer> container = GlobalDI::builder()
            .register_singleton<Impl1, SomeI>("first")
            .register_singleton<Impl2, SomeI>("second")
            .build();

    SomeI& some1= container->resolve<SomeI>("first");
    some1.do_smth();

    SomeI& some2 = container->resolve<SomeI>("second");
    some2.do_smth();

//    SomeI& wrong1 = container->resolve<SomeI>("secondddd");
//    wrong1.do_smth();

    SomeI& wrong2 = container->resolve<SomeI>();
    wrong2.do_smth();

    return EXIT_SUCCESS;
}