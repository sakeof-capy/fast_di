#ifndef INTCONTAINER_HPP_
#define INTCONTAINER_HPP_

#include <cstddef>

struct IntContainerInterface
{
    constexpr virtual ~IntContainerInterface() = default;
    constexpr virtual std::size_t get_i() const = 0;
};

struct IncrementorInterface
{
    constexpr virtual ~IncrementorInterface() = default;
    constexpr virtual std::size_t increment() const = 0;
};

struct IntContainer : IntContainerInterface, IncrementorInterface
{
    constexpr explicit IntContainer(std::size_t i) : i_ { i } {}

    constexpr ~IntContainer() override = default;

    static constexpr IntContainer create()
    {
        return IntContainer(DEFAULT_VALUE);
    }

    constexpr std::size_t get_i() const override
    {
        return i_;
    }

    constexpr std::size_t increment() const override
    {
        return i_ + 1;
    }

    std::size_t i_;

    static constexpr std::size_t DEFAULT_VALUE = 2u;
};

#endif //INTCONTAINER_HPP_
