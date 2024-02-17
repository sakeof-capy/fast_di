#ifndef DI_CONTAINERS_POSTGRESQLDATABASE_H
#define DI_CONTAINERS_POSTGRESQLDATABASE_H

#include "IDatabase.h"
#include "../Logger/FileLogger.h"
#include "../Models/TaskModel.h"
#include "../Models/UserModel.h"
#include <iostream>

class PostgreSQLDatabase : public IDatabase
{
public:
    explicit PostgreSQLDatabase(FileLogger& logger)
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
    static PostgreSQLDatabase create(FileLogger& logger)
    {
        return PostgreSQLDatabase { logger };
    }

private:
    FileLogger& logger_;
};

#endif //DI_CONTAINERS_POSTGRESQLDATABASE_H
