#ifndef WRAPWITHCREATORIFNOTCREATABLE_HPP_
#define WRAPWITHCREATORIFNOTCREATABLE_HPP_

namespace fast_di::dynamic_di::wrapper
{

template<typename Entity, typename... Args>
concept CreatableWith = requires(Args... args)
{
    { Entity::create(args...) } -> std::convertible_to<Entity>;
};

template<typename Entity, typename... Args>
concept NonCreatableWith = !CreatableWith<Entity, Args...>;

template<NonCreatableWith NonCreatable, typename... CreatorArgs>
struct WrapWithCreator : NonCreatable
{
    explicit WrapWithCreator(CreatorArgs... args)
        : NonCreatable(args...)
    {}

    static WrapWithCreator create(CreatorArgs... args)
    {
        return WrapWithCreator { args... };
    }
};

template<typename Dependency, typename... CreatorArgs>
struct SubscriberTraits
{
    using DependencyToBeInserted = Dependency;
};

template<typename Dependency, typename... CreatorArgs>
requires NonCreatableWith<Dependency, CreatorArgs...>
struct SubscriberTraits<Dependency, CreatorArgs...>
{
    using DependencyToBeInserted = WrapWithCreator<Dependency, CreatorArgs...>;
};

template<typename Dependency, typename... CreatorArgs>
using WrapWithCreatorIfNotCreatable = typename SubscriberTraits<
    Dependency,
    CreatorArgs...
>::DependencyToBeInserted;

}

#endif //WRAPWITHCREATORIFNOTCREATABLE_HPP_
