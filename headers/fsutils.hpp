#pragma once

#include <stdint.h>
#include <filesystem>
#include <gsl/gsl>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

std::pair<bool, std::vector<uint8_t>> ReadFileToBuffer(
    std::string_view filename, uint64_t readLength = 0 );

bool WriteBufferToFile( gsl::span<uint8_t> buff, std::string_view filename );

bool CreateDirIfUnexisting( fs::path newDirPath );

fs::path AppendStringToPath( fs::path destPath, std::string_view srcStr );