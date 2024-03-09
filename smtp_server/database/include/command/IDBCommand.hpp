#ifndef DI_CONTAINERS_IDBCOMMAND_HPP
#define DI_CONTAINERS_IDBCOMMAND_HPP

#include <optional>
#include <string>
#include <vector>
#include <map>

namespace Database::Command
{

class IDBCommand
{
public:
    using KeyParamType = std::string;
    using ValueParamType = std::string;
    using RawType = std::vector<std::string>;
    using ParamsType = std::map<KeyParamType, ValueParamType>;
    using ResultType = std::vector<RawType>;

public:
    virtual ~IDBCommand() = default;

public:
    virtual std::optional<ResultType> execute(const ParamsType& params) = 0;
};

}

#endif //DI_CONTAINERS_IDBCOMMAND_HPP
