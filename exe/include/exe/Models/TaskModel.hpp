#ifndef DI_CONTAINERS_TASKMODEL_HPP
#define DI_CONTAINERS_TASKMODEL_HPP

#include <string>

#include "classic_di/DISubscribe.hpp"

class TaskModel_
{
public:
    void set_name(const std::string& name)
    {
        name_ = name;
    }

    void set_executant(const std::string& executant)
    {
        executant_ = executant;
    }

    const std::string& get_name() const noexcept
    {
        return name_;
    }

    const std::string& get_executant() const noexcept
    {
        return executant_;
    }

public:
    static TaskModel_ create()
    {
        return {};
    }

private:
    std::string name_;
    std::string executant_;
};

MakeInjectableAs(TaskModel) Entity(TaskModel_)
With <
        Transient(TaskModel) ConstructedWith <> Injected
     > AsInjectionRulesFor(TaskModel)

#endif //DI_CONTAINERS_TASKMODEL_HPP
