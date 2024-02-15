#ifndef DI_CONTAINERS_ILOGGER_H
#define DI_CONTAINERS_ILOGGER_H

#include <string>

class ILogger
{
public:
    virtual ~ILogger() = default;

public:
    virtual void log(const std::string& message) = 0;
};

#endif //DI_CONTAINERS_ILOGGER_H
