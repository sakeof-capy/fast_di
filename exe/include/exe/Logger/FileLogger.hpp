#ifndef DI_CONTAINERS_FILELOGGER_HPP
#define DI_CONTAINERS_FILELOGGER_HPP

#include "ILogger.hpp"
#include <iostream>

#include "classic_di/DISubscribe.hpp"

class FileLogger : public ILogger,
                   private DISubscribe<SubscribeType::Singleton, FileLogger, ILogger>
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

template class DISubscribe<SubscribeType::Singleton, FileLogger, ILogger>;

#endif //DI_CONTAINERS_FILELOGGER_HPP
