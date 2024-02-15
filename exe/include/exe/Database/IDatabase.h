#ifndef DI_CONTAINERS_DATABASE_H
#define DI_CONTAINERS_DATABASE_H

class TaskModel;
class UserModel;

class IDatabase
{
public:
    virtual ~IDatabase() = default;

public:
    virtual void save_task(TaskModel&) = 0;
    virtual void save_user(UserModel&) = 0;
};

#endif //DI_CONTAINERS_DATABASE_H
