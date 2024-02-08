#include <iostream>

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>

class DIContainerBuilder;

class DIContainer
{
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
        if (found != singleton_dependencies_.end())
        {
            return resolve_singleton<Dependency>(found->second);
        }

        auto transient_found = transient_dependency_creators_.find(typeid(Dependency));
        if (transient_found != transient_dependency_creators_.end())
        {
            return resolve_transient<Dependency>(transient_found->second);
        }

        throw std::runtime_error("Non-registered dependency.");
    }

private:
    DIContainer
    (
        std::unordered_map<std::type_index, std::function<void*()>>&& singleton_dependencies,
        std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>>&& transient_dependency_creators
    )

        : singleton_dependencies_ { std::move(singleton_dependencies) }
        , transient_dependency_creators_ { std::move(transient_dependency_creators) }
    {}

    friend DIContainerBuilder;

private:
    std::unordered_map<std::type_index, std::function<void*()>> singleton_dependencies_;
    std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> transient_dependency_creators_;
    mutable std::vector<std::shared_ptr<void>> transient_instances;
};

class DIContainerBuilder
{
public:

    template<typename Interface, typename Dependency>
    DIContainerBuilder& add_singleton()
    {
        singleton_dependencies_[std::type_index(typeid(Interface))] = []() {
            static Dependency instance{};
            return &instance;
        };
        return *this;
    }

    template<typename Interface, typename Dependency>
    DIContainerBuilder& add_transient()
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
    std::unordered_map<std::type_index, std::function<void*()>> singleton_dependencies_;
    std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> transient_dependency_creators_;
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
        .add_transient<SomeInterface, SomeClass>()
        .build();

    SomeInterface& int_ref = container.resolve<SomeInterface>();
    int_ref.some_method();

    SomeInterface& int_ref2 = container.resolve<SomeInterface>();
    int_ref.some_method();

    SomeInterface& int_ref3 = container.resolve<SomeInterface>();
    int_ref.some_method();
    return EXIT_SUCCESS;
}