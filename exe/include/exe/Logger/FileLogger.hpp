#ifndef DI_CONTAINERS_FILELOGGER_HPP
#define DI_CONTAINERS_FILELOGGER_HPP

#include "ILogger.hpp"
#include <iostream>

#include "classic_di/DISubscribe.hpp"

class FileLogger_ : public ILogger
{
public:
    ~FileLogger_() override = default;

public:
    void log(const std::string& message) override
    {
        std::cout << "Logged to file: " << message << '\n';
    }

public:

public:
    static FileLogger_ create()
    {
        return {};
    }
};

//MakeInjectableAs(FileLogger) Entity(FileLogger_)
//With <
//        SingletonAsInterface(FileLogger, ILogger) ConstructedWith <> Injected
//     > AsInjectionRulesFor(FileLogger)

#endif //DI_CONTAINERS_FILELOGGER_HPP
