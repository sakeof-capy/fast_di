#ifndef DI_CONTAINERS_TASKCONTROLLER_HPP
#define DI_CONTAINERS_TASKCONTROLLER_HPP

#include "../Models/TaskModel.hpp"
#include "../Database/IDatabase.hpp"
#include "../Logger/ILogger.hpp"

#include "classic_di/DISubscribe.hpp"

class TaskController_
{
public:
    TaskController_(TaskModel_& model, IDatabase& database, ILogger& logger)
        : model_ { model }
        , database_ { database }
        , logger_ { logger }
    {}

    static TaskController_ create(TaskModel_& model, IDatabase& database, ILogger& logger)
    {
        return {model, database, logger};
    }

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

private:
    TaskModel_& model_;
    IDatabase& database_;
    ILogger& logger_;
};

//MakeInjectableAs(TaskController) Entity(TaskController_)
//With <
//        SingletonAsInterface(TaskController, TaskController_) ConstructedWith <TaskModel_&, IDatabase&, ILogger&> Injected
//     > AsInjectionRulesFor(TaskController)

#endif //DI_CONTAINERS_TASKCONTROLLER_HPP
