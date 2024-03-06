#ifndef DI_CONTAINERS_APPLICATION_HPP
#define DI_CONTAINERS_APPLICATION_HPP

#include "Controllers/TaskController.hpp"
#include "Controllers/UserController.hpp"
#include "Logger/ILogger.hpp"

#include "classic_di/DISubscribe.hpp"

#include <iostream>

class Application_
{
public:
    Application_(TaskController_& task_controller, UserController_& user_controller, ILogger& logger)
        : task_controller_ { task_controller }
        , user_controller_ { user_controller }
        , logger_ { logger }
    {}

public:
    void run()
    {
        const std::string task_name_message = "task_name=";
        const std::string task_executant_message = "task_executant=";
        const std::string user_name_message = "user_name=";
        const std::string user_password_message = "user_password=";
        std::string input{};

        logger_.log("App started.");

        do {
            std::cout << "Enter Command: ";
            std::cin >> input;
            if (input.starts_with(task_name_message))
            {
                const std::string name = extract_value(task_name_message, input);
                task_controller_.handle_name_modified(name);
            }
            else if (input.starts_with(task_executant_message))
            {
                const std::string executant = extract_value(task_executant_message, input);
                task_controller_.handle_executant_modified(executant);
            }
            else if (input.starts_with(user_name_message))
            {
                const std::string name = extract_value(user_name_message, input);
                user_controller_.handle_name_modified(name);
            }
            else if (input.starts_with(user_password_message))
            {
                const std::string password = extract_value(user_password_message, input);
                user_controller_.handle_password_modified(password);
            }
        } while (input != "end");

        task_controller_.handle_submit();
        user_controller_.handle_submit();
    }

private:
    static std::string extract_value(const std::string& prefix, const std::string& input)
    {
        return input.substr(prefix.size());
    }

private:
    TaskController_& task_controller_;
    UserController_& user_controller_;
    ILogger& logger_;
};







MakeInjectable(Application) Entity<Application_>::template
Withh
<
    DISubscribe<SubscribeType::Singleton, Application, Application, TaskController_&, UserController_&, ILogger&>
> AsInjectionRules;

//#define MakeInjectableAs(injectable_name) \
//class injectable_name : public
//
//#define Entity(original_name) InjectionConfiguration<original_name>::template Inner
//
//#define With
//#define AsInjectionRulesFor(name) ::UsableClass                                         \
//{                                                                                       \
//public:                                                                                 \
//    template<typename... Args>                                                          \
//    explicit name(Args&&... args) : BaseType(std::forward<Args>(args)...) {}            \
//    using SubscribersTuple = typename BaseType::SubscribersTuple;                       \
//};                                                                                      \
//inline void to_instantiate_##name() { static_cast<void>(name::SubscribersTuple {}); }
//
//#define SingletonAsInterface(Dependency, Interface) \
//typename DISubscribe_Utility_<SubscribeType::Singleton, Dependency, Interface>::template Inner
//
//#define Singleton(Dependency) SingletonAsInterface(Dependency, Dependency)
//
//#define TransientAsInterface(Dependency, Interface) \
//typename DISubscribe_Utility_<SubscribeType::Transient, Dependency, Interface>::template Inner
//
//#define Transient(Dependency) TransientAsInterface(Dependency, Dependency)
//
//#define ConstructedWith
//#define Injected ::Type

//class Application : public InjectionConfiguration<Application_>::template Inner
//        <typename DISubscribe_Utility_<SubscribeType::Singleton, Application, Application>::template Inner<TaskController&, UserController&, ILogger&>::Type
//        > ::UsableClass
//{
//public:
//    template<typename... Args>
//    explicit Application(Args&&... args) : BaseType(std::forward<Args>(args)...) {}
//    using SubscribersTuple = typename BaseType::SubscribersTuple;
//};
//inline void to_instantiate_Application() { static_cast<void>(Application::SubscribersTuple {}); }

//MakeInjectableAs(Application) Entity(Application_)
//With <
//        Singleton(Application) ConstructedWith <TaskController&, UserController&, ILogger&> Injected
//     > AsInjectionRulesFor(Application)

#endif //DI_CONTAINERS_APPLICATION_HPP
