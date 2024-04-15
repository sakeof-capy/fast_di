#ifndef DI_CONTAINERS_USERCONTROLLER_HPP
#define DI_CONTAINERS_USERCONTROLLER_HPP

#include "../Models/UserModel.hpp"
#include "../Database/IDatabase.hpp"
#include "../Logger/ILogger.hpp"

//#include "classic_di/DISubscribe.hpp"

class UserController_
{
public:
    UserController_(UserModel_& model, IDatabase& database, ILogger& logger)
            : model_ { model }
            , database_ { database }
            , logger_ { logger }
    {}

public:
    void handle_name_modified(const std::string& new_name)
    {
        model_.set_name(new_name);
        logger_.log("User's name modified to: " + model_.get_name());
    }

    void handle_password_modified(const std::string& new_password)
    {
        model_.set_password(new_password);
        logger_.log("User's password modified to: " + model_.get_password());
    }

    void handle_submit()
    {
        database_.save_user(model_);
    }

public:
    static UserController_ create(UserModel_& model, IDatabase& database, ILogger& logger)
    {
        return { model, database, logger };
    }

private:
    UserModel_& model_;
    IDatabase& database_;
    ILogger& logger_;
};
//
//MakeInjectableAs(UserController) Entity(UserController_)
//With <
//        SingletonAsInterface(UserController, UserController_) ConstructedWith <UserModel&, IDatabase&, ILogger&> Injected
//     > AsInjectionRulesFor(UserController)

#endif //DI_CONTAINERS_USERCONTROLLER_HPP
