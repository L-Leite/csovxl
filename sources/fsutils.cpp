#include "fsutils.hpp"

#include <fstream>

std::pair<bool, std::vector<uint8_t>> ReadFileToBuffer(
    std::string_view filename, uint64_t readLength /*= 0*/ )
{
    if ( fs::is_regular_file( filename.data() ) == false )
    {
        return { false, {} };
    }

    std::ifstream is( filename.data(), std::ios::binary | std::ios::ate );

    if ( is.is_open() == false )
    {
        return { false, {} };
    }

    if ( readLength == 0 )
    {
        uint64_t iFileSize = is.tellg();
        readLength = iFileSize;
    }

    std::vector<uint8_t> res( readLength );

    is.seekg( std::ios::beg );
    is.read( reinterpret_cast<char*>( res.data() ), readLength );

    return { true, res };
}

bool WriteBufferToFile( gsl::span<uint8_t> buff, std::string_view filename )
{
    std::ofstream os( filename.data(), std::ios::binary );

    if ( os.is_open() == false )
    {
        return false;
    }

    os.write( reinterpret_cast<char*>( buff.data() ), buff.size_bytes() );

    return true;
}

bool CreateDirIfUnexisting( fs::path newDirPath )
{
    if ( fs::is_directory( newDirPath ) == true )
    {
        return true;
    }

    std::error_code errorCode;
    fs::create_directories( newDirPath, errorCode );

    if ( errorCode )
    {
        return false;
    }

    return true;
}

fs::path AppendStringToPath( fs::path destPath, std::string_view srcStr )
{
    fs::path res = destPath;
    res += fs::path::preferred_separator;
    res += srcStr;
    return res;
}