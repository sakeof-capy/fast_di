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

///////////




int main()
{
    DIContainer container = DIContainerBuilder{}
            .register_transient<SomeClass, SomeInterface>()
            .register_transient<OtherClass>()
            .build();

    container.print_transient_deps();
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