#ifndef DI_CONTAINERS_POSTGRESQLDATABASE_HPP
#define DI_CONTAINERS_POSTGRESQLDATABASE_HPP

#include "IDatabase.hpp"
#include "../Logger/ILogger.hpp"
#include "../Models/TaskModel.hpp"
#include "../Models/UserModel.hpp"
#include <iostream>

#include "classic_di/DISubscribe.hpp"

class PostgreSQLDatabase_ : public IDatabase
{
public:
    explicit PostgreSQLDatabase_(ILogger& logger)
        : logger_ { logger }
    {
        logger_.log("Connected to PostgreSQL database.");
    }

public:
    void save_task(TaskModel_& task) override
    {
        std::cout << "Saved Task to PostgreSQL DB: name=" << task.get_name() << ", executant=" << task.get_executant() << '\n';
    }

    void save_user(UserModel_& user) override
    {
        std::cout << "Saved User to PostgreSQL DB: name=" << user.get_name() << ", password=" << user.get_password() << '\n';
    }

private:
    ILogger& logger_;
};

MakeInjectableAs(PostgreSQLDatabase) Entity(PostgreSQLDatabase_)
With <
        SingletonAsInterface(PostgreSQLDatabase, IDatabase) ConstructedWith <ILogger&> Injected
     > AsInjectionRulesFor(PostgreSQLDatabase)

#endif //DI_CONTAINERS_POSTGRESQLDATABASE_HPP
