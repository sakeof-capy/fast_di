#ifndef ENTITY_HPP_
#define ENTITY_HPP_

namespace fast_di::benchmarks
{

using Result = int;

template<Result ExpectedResult>
struct Expected
{
    static constexpr Result EXPECTED_RESULT = ExpectedResult;
};

template<typename ResultHolder>
static constexpr Result ExpectedResultOf = ResultHolder::EXPECTED_RESULT;

}

namespace fast_di::benchmarks::entity
{

struct Interface
{
public:
    virtual ~Interface() = default;
    virtual Result method() = 0;
};

struct Small : Interface, Expected<5436456>
{
    ~Small() override = default;

    static Small create()
    {
        return {};
    }

    Result method() override
    {
        return EXPECTED_RESULT;
    }
};

template<std::size_t Id>
struct IdInterface : Interface {};

struct Average : Interface, Expected<1123412>
{
    ~Average() override = default;

    Average()
        : buffer_ { 0 }
    {
        for (std::size_t i = 0u; i < BUFFER_SIZE; ++i)
        {
            buffer_[i] = i;
        }
    }

    static Average create()
    {
        return {};
    }

    Result method() override
    {
        buffer_[0] += 256;
        return EXPECTED_RESULT;
    }

    static constexpr std::size_t BUFFER_SIZE = 256;
    char buffer_[BUFFER_SIZE]{};
};

struct Big : Interface, Expected<3456345>
{
    ~Big() override = default;

    Big()
        : buffer_ { 0 }
    {
        for (std::size_t i = 0u; i < BUFFER_SIZE; ++i)
        {
            buffer_[i] = i;
        }
    }

    static Big create()
    {
        return {};
    }

    Result method() override
    {
        buffer_[0] += 5123;
        return EXPECTED_RESULT;
    }

    static constexpr std::size_t BUFFER_SIZE = 10240; // 10 KB
    char buffer_[BUFFER_SIZE]{};
};

template<std::size_t Id, typename... Args>
struct Dummy : IdInterface<Id>
{
    static Dummy create(Args...)
    {
        return {};
    }

    Result method() override
    {
        return Average::EXPECTED_RESULT;
    }

private:
    Average obj_;
};

}

#endif //ENTITY_HPP_
