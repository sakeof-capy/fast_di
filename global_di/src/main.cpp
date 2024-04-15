#include <iostream>
#include "../include/DITargetExample.hpp"
#include "../include/SomeDep.hpp"
#include "classic_di/GlobalDI.hpp"

int main()
{
    subscribe_all_dependencies();
    auto container = GlobalDI::build_container();
    auto& some_dep = container->resolve<SomeDep>();
    auto& some_dep2 = container->resolve<SomeOtherDep>();
    std::cout << some_dep.some_string() << std::endl;
    std::cout << some_dep2.some_string2() << std::endl;
    return EXIT_SUCCESS;
}