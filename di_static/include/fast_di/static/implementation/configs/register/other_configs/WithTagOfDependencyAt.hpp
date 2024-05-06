#ifndef WITHTAGOFDEPENDENCYAT_HPP_
#define WITHTAGOFDEPENDENCYAT_HPP_

#include <cstddef>

namespace fast_di::static_di
{

template<std::size_t Index>
struct WithTagOfDependencyAt
{
    const char* tag;
};

}

#endif //WITHTAGOFDEPENDENCYAT_HPP_
