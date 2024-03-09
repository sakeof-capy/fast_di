#ifndef DI_CONTAINERS_IDBCOMMAND_HPP
#define DI_CONTAINERS_IDBCOMMAND_HPP

#include <optional>
#include "DBCommandArgs.hpp"
#include "../QueryResponse.hpp"

namespace Database::Command
{

class IDBCommand
{
public:
    using ParamsType = DBCommandArgs;
    using ResultType = QueryResponse;
    using KeyArgType = typename ParamsType::KeyArgType;
    using ValueArgType = typename ParamsType::ValueArgType;

public:
    virtual ~IDBCommand() = default;

public:
    virtual std::optional<ResultType> execute(const ParamsType& params) = 0;
};

}

#endif //DI_CONTAINERS_IDBCOMMAND_HPP
