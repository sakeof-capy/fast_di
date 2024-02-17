#ifndef DI_CONTAINERS_POSTGRESQLDATABASE_HPP
#define DI_CONTAINERS_POSTGRESQLDATABASE_HPP

#include "IDatabase.hpp"
#include "../Logger/ILogger.hpp"
#include "../Models/TaskModel.hpp"
#include "../Models/UserModel.hpp"
#include <iostream>

class PostgreSQLDatabase : public IDatabase
{
public:
    explicit PostgreSQLDatabase(ILogger& logger)
        : logger_ { logger }
    {
        logger_.log("Connected to PostgreSQL database.");
    }

public:
    void save_task(TaskModel& task) override
    {
        std::cout << "Saved Task to PostgreSQL DB: name=" << task.get_name() << ", executant=" << task.get_executant() << '\n';
    }

    void save_user(UserModel& user) override
    {
        std::cout << "Saved User to PostgreSQL DB: name=" << user.get_name() << ", password=" << user.get_password() << '\n';
    }

public:
    static PostgreSQLDatabase create(ILogger& logger)
    {
        return PostgreSQLDatabase { logger };
    }

private:
    ILogger& logger_;
};

#endif //DI_CONTAINERS_POSTGRESQLDATABASE_HPP
