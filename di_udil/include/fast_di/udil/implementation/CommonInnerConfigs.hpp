#ifndef COMMONINNERCONFIGS_HPP_
#define COMMONINNERCONFIGS_HPP_

namespace fast_di::udil
{

template<typename Interface>
struct AsInterface {};

struct WithTag
{
    const char* tag;
};

template<std::size_t Index>
struct WithTagOfDependencyAt
{
    const char* tag;
};

template<typename... Args>
struct ConstructedWith {};

}

#endif //COMMONINNERCONFIGS_HPP_
