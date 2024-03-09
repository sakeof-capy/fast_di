#include "../include/database/QueryResponse.hpp"

namespace Database
{

QueryResponse::QueryResponse(const SizeType affected_rows)
        : container_()
        , affected_raws_(affected_rows)
{}

void QueryResponse::reserve(const SizeType initial_capacity)
{
    container_.reserve(initial_capacity);
}

void QueryResponse::add(const RowType& value)
{
    container_.push_back(value);
}

void QueryResponse::add(RowType&& value)
{
    container_.push_back(std::move(value));
}

QueryResponse::Iterator QueryResponse::begin() noexcept
{
    return container_.begin();
}

QueryResponse::Iterator QueryResponse::end() noexcept
{
    return container_.end();
}

QueryResponse::ConstIterator QueryResponse::begin() const noexcept
{
    return container_.begin();
}

QueryResponse::ConstIterator QueryResponse::end() const noexcept
{
    return container_.end();
}

QueryResponse::SizeType QueryResponse::size() const
{
    return container_.size();
}

bool QueryResponse::is_empty() const
{
    return container_.empty();
}

QueryResponse::SizeType QueryResponse::affected_rows() const
{
    return affected_raws_;
}

}
