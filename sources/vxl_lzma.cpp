#include "vxl_lzma.hpp"

#include "vxlstructures.hpp"

static void* SzAlloc(ISzAllocPtr p, size_t size)
{
    return malloc(size);
}
static void SzFree(ISzAllocPtr p, void* address)
{
    free(address);
}

static ISzAlloc g_Alloc = { SzAlloc, SzFree };

std::vector<uint8_t> VoxelDecompress(gsl::span<uint8_t> voxelData)
{
    if (voxelData.length_bytes() < sizeof(VxlBaseHeader_t))
    {
        return {};
    }

    VxlBaseHeader_t* pHeader =
        reinterpret_cast<VxlBaseHeader_t*>(voxelData.data());
    uint8_t* pDataStart = reinterpret_cast<uint8_t*>(
        reinterpret_cast<uint64_t>(voxelData.data()) + sizeof(VxlBaseHeader_t));

    size_t iCompressedSize = voxelData.length_bytes() - sizeof(VxlBaseHeader_t);
    size_t iDecompressedSize = pHeader->originalFileSize;

    std::vector<uint8_t> vOutData(pHeader->originalFileSize);

    ELzmaStatus status;

    auto res = LzmaDecode(vOutData.data(), &iDecompressedSize, pDataStart,
                          &iCompressedSize, pHeader->props, LZMA_PROPS_SIZE,
                          LZMA_FINISH_ANY, &status, &g_Alloc);

    if (res != SZ_OK)
    {
        return {};
    }

    return vOutData;
}
