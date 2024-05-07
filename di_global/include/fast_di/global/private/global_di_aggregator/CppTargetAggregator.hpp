#ifndef CPPTARGETAGGREGATOR_HPP_
#define CPPTARGETAGGREGATOR_HPP_

#include "IDataAggregator.hpp"
#include "DelimFileReader.hpp"

class CppTargetAggregator : public IDataAggregator
{
public:
    ~CppTargetAggregator() override = default;

public:

    void process_single_unit(const ProcessedUnitType& hppdi_file_path) override
    {
        const FileSystem::FileContentType DI_SUBSCRIBE_MARK = "DI_DYNAMIC_SUBSCRIBER_FOR(";
        DelimFileReader tokenizer(hppdi_file_path, "\n", 20u);

        aggregee_.include(hppdi_file_path);

        for
        (
            auto token_opt = tokenizer.next_token();
            token_opt.has_value();
            token_opt = tokenizer.next_token()
        )
        {
            auto& token = *token_opt;

            if (token.starts_with(DI_SUBSCRIBE_MARK))
            {
                std::size_t i = DI_SUBSCRIBE_MARK.size();
                for (; i < token.size() && token[i] != ')'; ++i);
                auto subscriber_type = token.substr(DI_SUBSCRIBE_MARK.size(), i - 5);
                aggregee_.add_subscriber_type(std::move(subscriber_type));
            }
        }
    }

    const DataAggregationType& get_aggregated_data() const noexcept override
    {
        return aggregee_;
    }

private:
    DataAggregationType aggregee_;
};


#endif //CPPTARGETAGGREGATOR_HPP_
