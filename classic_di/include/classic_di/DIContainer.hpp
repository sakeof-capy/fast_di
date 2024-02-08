#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>

class DIContainerBuilder;

class DIContainer
{
public:
    using SingletonDependenciesMap = std::unordered_map<std::type_index, std::function<void*()>>;
    using TransientDependenciesMap = std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>>;

private:
    template<typename Dependency>
    Dependency& resolve_singleton(const std::function<void*()>& creator) const
    {
        void* ptr_to_singleton = creator();
        return *static_cast<Dependency*>(ptr_to_singleton);
    }

    template<typename Dependency>
    Dependency& resolve_transient(const std::function<std::shared_ptr<void>()>& creator) const
    {
        std::shared_ptr<void>& ptr_to_transient = transient_instances.emplace_back(creator());
        return *std::static_pointer_cast<Dependency>(ptr_to_transient);
    }

public:
    template<typename Dependency>
    Dependency& resolve() const
    {
        auto found = singleton_dependencies_.find(typeid(Dependency));
        if (found != singleton_dependencies_.cend())
        {
            return resolve_singleton<Dependency>(found->second);
        }

        auto transient_found = transient_dependency_creators_.find(typeid(Dependency));
        if (transient_found != transient_dependency_creators_.cend())
        {
            return resolve_transient<Dependency>(transient_found->second);
        }

        throw std::runtime_error("Non-registered dependency.");
    }

private:
    DIContainer
    (
        SingletonDependenciesMap&& singleton_dependencies,
        TransientDependenciesMap&& transient_dependency_creators
    )

        : singleton_dependencies_        { std::move(singleton_dependencies) }
        , transient_dependency_creators_ { std::move(transient_dependency_creators) }
    {}

    friend DIContainerBuilder;

private:
    SingletonDependenciesMap singleton_dependencies_;
    TransientDependenciesMap transient_dependency_creators_;
    mutable std::vector<std::shared_ptr<void>> transient_instances;
};