#include <iostream>
#include "classic_di/DIContainerBuilder.hpp"

class SomeInterface
{
public:
    virtual ~SomeInterface() = default;

public:
    virtual void some_method() = 0;
};

class SomeClass : public SomeInterface
{
public:
    ~SomeClass() override
    {
        std::cout << "Destructed" << std::endl;
    }

public:
    void some_method() override
    {
        std::cout << "Method called" << std::endl;
    }
};

int main()
{
    DIContainer container = DIContainerBuilder{}
            .register_singleton<SomeClass, SomeInterface>()
            .register_singleton<int>()
            .build();

    SomeInterface& some_class_ref1 = container.resolve<SomeInterface>();
    some_class_ref1.some_method();

    SomeInterface& some_class_ref2 = container.resolve<SomeInterface>();
    some_class_ref2.some_method();

    SomeInterface& some_class_ref3 = container.resolve<SomeInterface>();
    some_class_ref3.some_method();

    int& injected_int = container.resolve<int>();
    std::cout << injected_int << std::endl;

    return EXIT_SUCCESS;
}