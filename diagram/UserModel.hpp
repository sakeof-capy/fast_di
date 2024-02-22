#ifndef DI_CONTAINERS_USERMODEL_HPP
#define DI_CONTAINERS_USERMODEL_HPP

#include <string>

class UserModel
{
public:
    void set_name(const std::string& name)
    {
        name_ = name;
    }

    void set_password(const std::string& password)
    {
        password_ = password;
    }

    const std::string& get_name() const noexcept
    {
        return name_;
    }

    const std::string& get_password() const noexcept
    {
        return password_;
    }

public:
    static UserModel create()
    {
        return {};
    }

private:
    std::string name_;
    std::string password_;
};

#endif //DI_CONTAINERS_USERMODEL_HPP
