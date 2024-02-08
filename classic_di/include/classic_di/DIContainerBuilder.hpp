#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>

#include "DIContainer.hpp"

class DIContainerBuilder
{
private:
    using SingletonDependenciesMap = std::unordered_map<std::type_index, std::function<void*()>>;
    using TransientDependenciesMap = std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>>;

public:
    template<typename Dependency, typename Interface = Dependency>
    DIContainerBuilder& register_singleton()
    {
        singleton_dependencies_[std::type_index(typeid(Interface))] = []() {
            static Dependency instance{};
            return &instance;
        };
        return *this;
    }

    template<typename Dependency, typename Interface = Dependency>
    DIContainerBuilder& register_transient()
    {
        transient_dependency_creators_[std::type_index(typeid(Interface))] = []() {
            return std::make_shared<Dependency>();
        };
        return *this;
    }

    DIContainer build()
    {
        return DIContainer { std::move(singleton_dependencies_),
                             std::move(transient_dependency_creators_) };
    }

private:
    SingletonDependenciesMap singleton_dependencies_;
    TransientDependenciesMap transient_dependency_creators_;
};