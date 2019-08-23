#pragma once

#include <cstdint>
#include <gsl/gsl>

std::vector<uint8_t> VoxelDecompress(gsl::span<uint8_t> voxelData);