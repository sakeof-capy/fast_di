#ifndef DI_CONTAINERS_TASKCONTROLLER_H
#define DI_CONTAINERS_TASKCONTROLLER_H

#include "../Models/TaskModel.h"
#include "../Database/PostgreSQLDatabase.h"
#include "../Logger/FileLogger.h"

class TaskController
{
public:
    TaskController(TaskModel& model, PostgreSQLDatabase& database, FileLogger& logger)
        : model_ { model }
        , database_ { database }
        , logger_ { logger }
    {}

public:
    void handle_name_modified(const std::string& new_name)
    {
        model_.set_name(new_name);
        logger_.log("Task's name modified to: " + model_.get_name());
    }

    void handle_executant_modified(const std::string& new_executant)
    {
        model_.set_executant(new_executant);
        logger_.log("Task's executant modified to: " + model_.get_executant());
    }

    void handle_submit()
    {
        database_.save_task(model_);
    }

public:
    static TaskController create(TaskModel& model, PostgreSQLDatabase& database, FileLogger& logger)
    {
        return { model, database, logger };
    }

private:
    TaskModel& model_;
    PostgreSQLDatabase& database_;
    FileLogger& logger_;
}; // TaskController

#endif //DI_CONTAINERS_TASKCONTROLLER_H
