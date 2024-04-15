#ifndef SOMEDEP_HPP_
#define SOMEDEP_HPP_

#include <string>

//namespace SOME_NAMESPACE
//{

class SomeDep
{
public:
    static constexpr SomeDep create()
    {
        return {};
    }

public:
    constexpr std::string some_string() const
    {
        return "WORKS";
    }
};

class SomeOtherDep
{
public:
    static constexpr SomeOtherDep create(SomeDep dep)
    {
        return SomeOtherDep(dep);
    }

public:
    constexpr explicit SomeOtherDep(SomeDep dep)
            : dep_{dep}
    {}

public:
    constexpr std::string some_string2() const
    {
        return "WORKS2";
    }

private:
    SomeDep dep_;
};

//}

#endif //SOMEDEP_HPP_
