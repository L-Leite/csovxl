#include <iostream>

#include "cmdparser.hpp"
#include "fsutils.hpp"
#include "vxl_lzma.hpp"

inline void PrintHelp()
{
    std::cout
        << "Decompresses Voxel configuration files (with '.vxl' extension) "
           "used by Nexon's Counter-Strike Online.\n"
        << "\n"
        << "Usages:\n"
        << "\tcsovxl [INPUT FILE]\n"
        << "\tcsovxl [INPUT FILE] -o [OUTPUT FILE]\n"
        << "Examples:\n"
        << "\tcsovxl 01553060153843999001.vxl\n"
        << "\tcsovxl 01553060153843999001.vxl -o "
           "01553060153843999001.vxl_data\n"
        << "\n"
        << "Options:\n"
        << "\t-h\tPrints this help text\n"
        << "\t-o\tWhere to write the decrypted file\n"
        << "\n";
}

int main(int argc, const char* argv[])
{
    CmdParser cmd(argv, argc);

    if (cmd.GetArgsNum() < 2 || cmd.HasOption("-h") == true)
    {
        PrintHelp();
        return 0;
    }

    std::filesystem::path sourceFilePath = cmd.GetByIndex(1);
    std::filesystem::path outFilePath;

    std::cout << "Using input file " << sourceFilePath << "\n";

    std::string_view szvOutOption = cmd.GetOption("-o");

    if (szvOutOption.empty() == false)
    {
        outFilePath = szvOutOption;
        std::cout << "Using user's chosen output file " << outFilePath << "\n";
    }
    else
    {
        outFilePath = sourceFilePath;
        outFilePath.replace_extension(".dec_data");
        std::cout << "Using output file " << outFilePath << "\n";
    }

    auto [bFileRead, vDataBuf] = ReadFileToBuffer(sourceFilePath.string());

    if (bFileRead == false)
    {
        std::cerr << "Failed to read encrypted file " << sourceFilePath << "\n";
        return 1;
    }

    auto vDecData = VoxelDecompress(vDataBuf);

    std::cout << "Data's new decrypted size is " << vDecData.size() << "\n";

    const bool writeRes = WriteBufferToFile(vDecData, outFilePath.string());

    if (writeRes == false)
    {
        std::cerr << "Failed to write decrypted file to " << outFilePath
                  << "\n";
        return 1;
    }

    std::cout << "Wrote decrypted file to " << outFilePath << "\n";

    return 0;
}
