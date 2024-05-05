#ifndef FILE_SYSTEM_HPP_
#define FILE_SYSTEM_HPP_
#include <filesystem>
#include <string>

namespace FileSystem
{

using PathType = std::filesystem::path;
using FileContentType = std::string;
using FileCharType = typename FileContentType::value_type;

}

#endif // !FILE_SYSTEM_HPP_