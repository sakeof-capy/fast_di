#include "classic_di/DIContainerBuilder.hpp"
#include "classic_di/type_traits/TypeLists.hpp"
#include "classic_di/type_traits/FunctionTypeTraits.hpp"
#include "../include/exe/Application.hpp"
#include "../include/exe/Database/PostgreSQLDatabase.hpp"
#include "../include/exe/Logger/FileLogger.hpp"

class ConsoleLogger : public ILogger
{
public:
    ~ConsoleLogger() override = default;

public:
    void log(const std::string& message) override
    {
        std::cout << "Logged to console: " << message << '\n';
    }

public:
    static ConsoleLogger create()
    {
        return {};
    }
};

int main()
{
    DIContainerBuilder builder;
    builder.register_singleton_params_deduced<Application>();
    builder.register_singleton_params_deduced<PostgreSQLDatabase, IDatabase>();
    builder.register_transient_params_deduced<TaskModel>();
    builder.register_singleton_params_deduced<ConsoleLogger, ILogger>();
    builder.register_singleton_params_deduced<TaskController>();
    builder.register_singleton_params_deduced<UserController>();
    builder.register_transient_params_deduced<UserModel>();

    std::unique_ptr<DIContainer> container = builder.build();

    Application& app = container->resolve<Application>();
    app.run();

    return EXIT_SUCCESS;
}