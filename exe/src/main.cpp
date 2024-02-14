#include <iostream>
#include "classic_di/DIContainerBuilder.hpp"


struct OtherClass
{
    static OtherClass create() { return {}; }
};

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
    explicit SomeClass(OtherClass a) : a_{ a } {}

public:
    static SomeClass create(OtherClass a)
    {
        return SomeClass(a);
    }
public:
    ~SomeClass() override
    {
        std::cout << "Destroyed" << std::endl;
    }

public:
    void some_method() override
    {
        std::cout << "Method called" << std::endl;
    }

private:
    OtherClass a_;
};

int main()
{
    std::unique_ptr<DIContainer> container = DIContainerBuilder{}
            .register_singleton<SomeClass, SomeInterface>()
            .register_transient<OtherClass>()
            .build();

    SomeInterface& some_class_ref1 = container->resolve<SomeInterface>();
    some_class_ref1.some_method();

    SomeInterface& some_class_ref2 = container->resolve<SomeInterface>();
    some_class_ref2.some_method();

    SomeInterface& some_class_ref3 = container->resolve<SomeInterface>();
    some_class_ref3.some_method();


    return EXIT_SUCCESS;
}