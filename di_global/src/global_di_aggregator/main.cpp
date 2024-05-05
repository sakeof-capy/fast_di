#include <iostream>
#include <fstream>
#include "DelimFileReader.hpp"
#include "FileIterator.hpp"
#include "CppTargetAggregator.hpp"

using FileSystem::PathType;

const std::string HPP_DEFAULT = "#ifndef SUBSCRIBE_ALL_GLOBAL_DI_HPP_\n"
                                "#define SUBSCRIBE_ALL_GLOBAL_DI_HPP_\n"
                                "\n"
                                "void subscribe_all_dependencies();\n"
                                "\n"
                                "#endif //SUBSCRIBE_ALL_GLOBAL_DI_HPP_";

void write_all(const PathType& file, const FileSystem::FileContentType& content)
{
    std::ofstream outputFile(file);

    if (outputFile.is_open())
    {
        outputFile << content;
        outputFile.close();
        std::cout << "Successful output to " << file.string() << std::endl;
    }
    else
    {
        std::cerr << "Error opening the file: " << file.string() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <root> <target_hpp> <target_cpp>\n";
        return EXIT_FAILURE;
    }

    std::cout << "root: " << argv[1] << std::endl;
    std::cout << "target hpp: " << argv[2] << std::endl;
    std::cout << "target cpp: " << argv[3] << std::endl;

    const std::string root = argv[1];
    const std::string target_hpp = argv[2];
    const std::string target_cpp = argv[3];

    FileIterator file_iterator { root, L"\\w+\\.hppdi$"};
    CppTargetAggregator aggregator{};

    for
    (
        auto file_path_optional = file_iterator.next_file();
        file_path_optional.has_value();
        file_path_optional = file_iterator.next_file()
    )
    {
        const auto& file_path = *file_path_optional;
        std::wcout << file_path.c_str() << ":" << std::endl;
        aggregator.process_single_unit(file_path);
    }

    const auto aggregated_cpp = aggregator.get_aggregated_data().to_file_content();
    write_all(target_hpp, HPP_DEFAULT);
    write_all(target_cpp, aggregated_cpp);

    return EXIT_SUCCESS;
}