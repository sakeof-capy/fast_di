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
        std::cout << "Destroyed" << std::endl;
    }

public:
    void some_method() override
    {
        std::cout << "Method called" << std::endl;
    }
};

///////////

template<typename...>
struct pack {};

template<typename T>
struct function_traits;

template<typename ReturnValue_, typename... Params_>
struct function_traits<ReturnValue_(Params_...)>
{
    using ReturnValue = ReturnValue_;
    using Params = pack<Params_...>;
};

template<typename Head, typename... Tail>
void print_type_names()
{
    std::cout << typeid(Head).name() << std::endl;

    if constexpr (sizeof...(Tail) > 0)
    {
        print_type_names<Tail...>();
    }
}

template<typename... Pack>
void print_type_names_pack(pack<Pack...>)
{
    print_type_names<Pack...>();
}

struct SomeType
{
    static int some_func(int y, double x, SomeClass)
    {
        return 0;
    }
};

template<typename T>
void print_type_names_of_some_func()
{
    using params = typename function_traits<decltype(T::some_func)>::Params;
    print_type_names_pack(params{});
}

///////////



int some_func(double y, int x, SomeClass)
{
    return 0;
}


int main()
{
    print_type_names_of_some_func<SomeType>();

    DIContainer container = DIContainerBuilder{}
            .register_transient<SomeClass, SomeInterface>()
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