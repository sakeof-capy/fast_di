#ifndef DISUBSCRIBE_HPP_
#define DISUBSCRIBE_HPP_

#include "GlobalDI.hpp"
#include <iostream>

enum class SubscribeType
{
    Singleton,
    Transient,
};

template<typename Entity, typename... Args>
concept CreatableWith = requires(Args... args)
{
    { Entity::create(args...) } -> std::same_as<Entity>;
};

template<typename Entity, typename... Args>
concept NonCreatableWith = !CreatableWith<Entity, Args...>;

template<NonCreatableWith NonCreatable, typename... CreatorArgs>
struct WrapWithCreator : NonCreatable
{
    explicit WrapWithCreator(CreatorArgs... args) : NonCreatable(args...)
    {}

    static constexpr WrapWithCreator create(CreatorArgs... args)
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
using DependencyToBeInsertedType = typename SubscriberTraits<Dependency, CreatorArgs...>::DependencyToBeInserted;

template<SubscribeType SUBSCRIBE_TYPE, typename Dependency, typename Interface, typename... CreatorArgs>
    //requires std::derived_from<Dependency, Interface> || std::same_as<Dependency, Interface>
class DISubscribe
{
public:
    DISubscribe()
    {
//        std::cout << s_IS_SUBSCRIBED << std::endl;
        verify_subscribed();
    }

public:
    static constexpr Dependency create(CreatorArgs... args)
    {
        return Dependency{ args... };
    }

private:
    static void verify_subscribed()
    {
        static_cast<void>(s_IS_SUBSCRIBED);
    }

    static bool subscribe_to_global_di()
    {
        using ToInsertType = DependencyToBeInsertedType<Dependency, CreatorArgs...>;
        DIContainerBuilder& builder = GlobalDI::builder();
        switch (SUBSCRIBE_TYPE)
        {
            case SubscribeType::Singleton:
                std::cout << "Subscribed to singleton as " << typeid(ToInsertType).name() << " to interface " << typeid(Interface).name() << std::endl;
                builder.register_singleton<ToInsertType, Interface>();
                return true;
            case SubscribeType::Transient:
                std::cout << "Subscribed to transient as " << typeid(ToInsertType).name() << " to interface " << typeid(Interface).name() << std::endl;
                builder.register_transient<ToInsertType, Interface>();
                return true;
            default:
                return false;
        }
    }

private:
    static inline bool s_IS_SUBSCRIBED = subscribe_to_global_di();
};

#endif //DISUBSCRIBE_HPP_
