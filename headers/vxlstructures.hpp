#pragma once

#include <cstdint>

#include <LzmaDec.h>

constexpr const int VXL_HEADER_MAGIC = 'vosc';  // "csov" in little endian
constexpr const int VXL_HEADER_MOREMAGIC = '....';
constexpr const int VXL_HEADER_VERSION = 20151001;  // 2015/10/01

#pragma pack(push, 1)
struct VxlBaseHeader_t
{
    char magic[4];
    char moreMagic[4];     // maybe it has some other purpose
    std::int32_t version;  // latest is 20151001 (decimal)
    std::uint32_t originalFileSize;
    std::uint8_t props[LZMA_PROPS_SIZE];
};
#pragma pack(pop)

static_assert(sizeof(VxlBaseHeader_t) == 21, "The header's size must be 21");
