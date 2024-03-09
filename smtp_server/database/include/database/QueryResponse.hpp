#ifndef FAST_DI_LIBS_QUERY_RESPONSE_HPP
#define FAST_DI_LIBS_QUERY_RESPONSE_HPP

#include <vector>
#include <string>

namespace Database
{

class QueryResponse
{
public:
    using RowType = std::vector<std::string>;
    using ContainerType = std::vector<RowType>;
    using SizeType = typename ContainerType::size_type;
    using Iterator = typename ContainerType::iterator;
    using ConstIterator = typename ContainerType::const_iterator;

public:
    explicit QueryResponse(SizeType affected_rows);

public:
    void reserve(SizeType initial_capacity);
    SizeType size() const;
    bool is_empty() const;
    void add(const RowType& value);
    void add(RowType&& value);
    SizeType affected_rows() const;

public:
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;

private:
    ContainerType container_;
    SizeType affected_raws_;
};

}

#endif //FAST_DI_LIBS_QUERY_RESPONSE_HPP
