#ifndef DI_CONTAINERS_FILELOGGER_H
#define DI_CONTAINERS_FILELOGGER_H

#include "ILogger.h"
#include <iostream>

class FileLogger : public ILogger
{
public:
    ~FileLogger() override = default;

public:
    void log(const std::string& message) override
    {
        std::cout << "Logged to file: " << message << '\n';
    }

public:
    static FileLogger create()
    {
        return {};
    }
};

#endif //DI_CONTAINERS_FILELOGGER_H
