#include <iostream>

template<typename Entity>
class DebugPrinter
{
public:
    explicit DebugPrinter(const bool is_moved = false)
            : entity_name_(get_entity_name())
            , is_moved_ { is_moved }
    {
        std::cout << "Constructed: " << entity_name_ << std::endl;
    }

    DebugPrinter(const DebugPrinter& other)
            : DebugPrinter(other.is_moved_)
    {
        std::cout << "Copied: " << entity_name_ << std::endl;
    }

    DebugPrinter(DebugPrinter&& other) noexcept
            : DebugPrinter(other.is_moved_)
    {
        other.is_moved_ = true;
        std::cout << "Moved: " << entity_name_ << std::endl;
    }

    DebugPrinter& operator=(const DebugPrinter& other)
    {
        entity_name_ = other.entity_name_;
        is_moved_ = other.entity_name_;
        std::cout << "Copied: " << entity_name_ << std::endl;
    }

    DebugPrinter& operator=(DebugPrinter&& other) noexcept
    {
        entity_name_ = other.entity_name_;
        is_moved_ = other.is_moved_;
        other.is_moved_ = true;
        std::cout << "Moved: " << entity_name_ << std::endl;
        return *this;
    }

public:
    virtual ~DebugPrinter()
    {
        if (!is_moved_)
        {
            std::cout << "Destroyed: " << entity_name_ << std::endl;
        }
        else
        {
            std::cout << "Destroyed moved: " << entity_name_ << std::endl;
        }
    }

private:
    [[nodiscard]] std::string_view get_entity_name() const
    {
        return typeid(Entity).name();
    }

private:
    std::string_view entity_name_;
    bool is_moved_;
};