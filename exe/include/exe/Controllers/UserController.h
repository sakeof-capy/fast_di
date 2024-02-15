#ifndef DI_CONTAINERS_USERCONTROLLER_H
#define DI_CONTAINERS_USERCONTROLLER_H

#include "../Models/UserModel.h"
#include "../Database/PostgreSQLDatabase.h"
#include "../Logger/FileLogger.h"

class UserController
{
public:
    UserController(UserModel model, PostgreSQLDatabase database, FileLogger logger)
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
    static UserController create(UserModel model, PostgreSQLDatabase database, FileLogger logger)
    {
        return UserController { model, database, logger };
    }

private:
    UserModel model_;
    PostgreSQLDatabase database_;
    FileLogger logger_;
};

#endif //DI_CONTAINERS_USERCONTROLLER_H
