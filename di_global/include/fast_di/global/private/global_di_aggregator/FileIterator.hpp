#ifndef FILE_ITERATOR_HPP_
#define FILE_ITERATOR_HPP_

#include "FileSystem.hpp"
#include <optional>
#include <filesystem>
#include <regex>

class FileIterator
{
private:
    using IteratorType = std::filesystem::recursive_directory_iterator;
public:
    using PathType = FileSystem::PathType;
    using PathStringType = typename PathType::string_type;
    using RegexType = std::conditional_t<std::is_same_v<PathStringType, std::wstring>, std::wregex, std::regex>;
public:
    FileIterator(const PathType& folder_path, const PathStringType& regex);

public:
    std::optional<PathType> next_file() noexcept;

private:
    void skip_all_unneeded() noexcept;
    bool is_needed(const PathType& path) const noexcept;

private:
    IteratorType iterator_;
    RegexType regular_expression_;
};

#endif // !FILE_ITERATOR_HPP_




