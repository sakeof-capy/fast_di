#ifndef DI_CONTAINERS_USERCONTROLLER_HPP
#define DI_CONTAINERS_USERCONTROLLER_HPP

#include "../Models/UserModel.hpp"
#include "../Database/IDatabase.hpp"
#include "../Logger/ILogger.hpp"

#include "classic_di/DISubscribe.hpp"

class UserController : private DISubscribe<SubscribeType::Singleton, UserController, UserController,
        UserModel&, IDatabase&, ILogger&>
{
public:
    UserController(UserModel& model, IDatabase& database, ILogger& logger)
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

private:
    UserModel& model_;
    IDatabase& database_;
    ILogger& logger_;
};

#endif //DI_CONTAINERS_USERCONTROLLER_HPP
