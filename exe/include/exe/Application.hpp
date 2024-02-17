#ifndef DI_CONTAINERS_APPLICATION_HPP
#define DI_CONTAINERS_APPLICATION_HPP

#include "Controllers/TaskController.hpp"
#include "Controllers/UserController.hpp"
#include "Logger/ILogger.hpp"

#include <iostream>

class Application
{
public:
    Application(TaskController& task_controller, UserController& user_controller, ILogger& logger)
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

//        std::cout << &logger_ << std::endl;
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

public:
    static Application create(TaskController& task_controller, UserController& user_controller, ILogger& logger)
    {
        return { task_controller, user_controller, logger };
    }

private:
    TaskController& task_controller_;
    UserController& user_controller_;
    ILogger& logger_;
};

#endif //DI_CONTAINERS_APPLICATION_HPP
