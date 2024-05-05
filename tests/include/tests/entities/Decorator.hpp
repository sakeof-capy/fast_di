#ifndef DECORATOR_HPP_
#define DECORATOR_HPP_

class Interface
{
public:
    constexpr virtual ~Interface() = default;

public:
    constexpr virtual const char* do_something() const = 0;
};

class Implementation : public Interface
{
public:
    constexpr Implementation() = default;

    static constexpr Implementation create()
    {
        return {};
    }

public:
    constexpr const char* do_something() const override
    {
        return DO_RESULT;
    }

public:
    static constexpr const char* DO_RESULT = "RESULT_OF_DO";
};

class Decorator : public Interface
{
public:
    explicit constexpr Decorator(const Implementation& doer)
        : doer_ { doer }
    {}

    static constexpr Decorator create(const Implementation& doer)
    {
        return Decorator { doer };
    }

public:
    constexpr const char* do_something() const override
    {
        if (doer_.do_something() == Implementation::DO_RESULT)
        {
            return DO_RESULT;
        }
        else
        {
            return "WRONG_RESULT";
        }
    }

private:
    const Implementation& doer_;

public:
    static constexpr const char* DO_RESULT = "RESULT_OF_DO2222";
};

#endif //DECORATOR_HPP_
