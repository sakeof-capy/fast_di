#ifndef DI_CONTAINERS_DATABASE_H
#define DI_CONTAINERS_DATABASE_H

class TaskModel_;
class UserModel_;

class IDatabase
{
public:
    virtual ~IDatabase() = default;

public:
    virtual void save_task(TaskModel_&) = 0;
    virtual void save_user(UserModel_&) = 0;
};

#endif //DI_CONTAINERS_DATABASE_H
