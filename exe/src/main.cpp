#include <iostream>
#include "classic_di/DIContainerBuilder.hpp"
#include "../include/exe/Application.h"
#include "classic_di/type_traits/TypeLists.hpp"

class SomeInterface
{
public:
    virtual ~SomeInterface() = default;

public:
    virtual void do_smth() = 0;
};

class Dependency : public SomeInterface
{
public:
    static Dependency create()
    {
        return Dependency{};
    }

public:
    ~Dependency() override = default;

public:
    void do_smth() override
    {
        std::cout << "WORKS~!!!!" << std::endl;
    }

public:
    int x = 0;
};

class App
{
public:
    explicit App(SomeInterface& dependency) : dependency_ { dependency } {}

public:
    static App create(SomeInterface& dependency)
    {
        return App { dependency };
    }

public:
    void use()
    {
        dependency_.do_smth();
    }

private:
    SomeInterface& dependency_;
};


template<typename... T>
void f(TypeTraits::pack<T...>)
{
    return;
}

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

//    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
//            .register_singleton<App>()
//            .register_singleton<Dependency, SomeInterface>()
//            .build();

//    App& app = container->resolve<App>();
//    app.use();

//    auto res = TypeTraits::map_to_tuple(TypeTraits::pack<int, float>{}, []<typename T>() { return typeid(T).name(); });
//    std::cout << get<0>(res) << std::endl;
//    std::cout << get<1>(res) << std::endl;

//    int a = 2;
//    auto res = TypeTraits::map_to_tuple(TypeTraits::pack<>{}, [&a]<typename T>() -> int& { std::cout << typeid(T).name() << a << std::endl; return a;});
////    std::cout << get<0>(res) << std::endl;
////    std::cout << get<1>(res) << std::endl;
    return EXIT_SUCCESS;
}