#include <gtest/gtest.h>
#include <string_view>
#include "classic_di/DIContainerBuilder.hpp"

const std::string DO_SOMETHING_RESULT = "do_something_result12r1r1";
const std::string DODO_RESULT = "dododoododododoodod";
const std::string INTERCEPTION = "INTERCEPTED: ";

class SomeInterface
{
public:
    virtual ~SomeInterface() = default;

public:
    virtual std::string do_something() = 0;
};

class SomeInterceptor : public SomeInterface
{
public:
    explicit SomeInterceptor(SomeInterface& decoratee)
        : decoratee_ { decoratee }
    {}

    static SomeInterceptor create(SomeInterface& decoratee)
    {
        return SomeInterceptor { decoratee };
    }

    ~SomeInterceptor() override = default;

public:
    std::string do_something() override
    {
        return INTERCEPTION + decoratee_.do_something();
    }

private:
    SomeInterface& decoratee_;
};

class SomeDoer : public SomeInterface
{
public:
    ~SomeDoer() override = default;

public:
    std::string do_something() override
    {
        return DO_SOMETHING_RESULT;
    }

    static SomeDoer create()
    {
        return {};
    }
};

class Dummy
{
public:
    std::string_view dodo() const
    {
        return DODO_RESULT;
    }

    static Dummy create()
    {
        return {};
    }
};

class CommandUser
{
public:
    CommandUser(const Dummy& dummy, SomeInterface& some_instance)
            : dummy_ { dummy }
            , some_instance_ { some_instance }
    {}

public:
    static CommandUser create(Dummy& dummy, SomeInterface& some_instance)
    {
        return CommandUser { dummy, some_instance };
    }

    std::string_view use_command()
    {
        return dummy_.dodo();
    }

    std::string_view use_some_instance()
    {
        return some_instance_.do_something();
    }

private:
    const Dummy& dummy_;
    SomeInterface& some_instance_;
};

TEST(BasicDITest, DI)
{
    DIContainer container = DIContainerBuilder{}
        .register_singleton<CommandUser>()
            .with_dependency_tag<Dummy>("some-tag-dummy")
            .done()
        .register_transient<Dummy>()
            .with_tag("some-tag-dummy")
            .done()
        .register_singleton<SomeDoer>()
            .as_interface<SomeInterface>()
            .done()
        .add_interceptor<SomeInterceptor, SomeInterface>()
        .build();

    CommandUser& user = container.resolve<CommandUser>();
    ASSERT_EQ(user.use_command(), DODO_RESULT);
    ASSERT_EQ(user.use_some_instance(), DO_SOMETHING_RESULT);
}