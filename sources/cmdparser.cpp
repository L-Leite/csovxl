#include "cmdparser.hpp"

#include <algorithm>

CmdParser::CmdParser(const char** argv, int argc)
{
    const char** begin = argv;
    const char** end = argv + argc;

    std::vector<std::string_view> vArgs;

    std::for_each(begin, end, [&](const char* cur) { vArgs.push_back(cur); });
    this->m_vArgs = std::move(vArgs);
}

std::string_view CmdParser::GetOption(std::string_view targetOpt) const
{
    auto it = std::find(this->m_vArgs.begin(), this->m_vArgs.end(), targetOpt);

    if (it != this->m_vArgs.end() && ++it != this->m_vArgs.end())
    {
        return *it;
    }

    return {};
}

std::string_view CmdParser::GetByIndex(size_t targetIndex) const
{
    return this->m_vArgs.at(targetIndex);
}

bool CmdParser::HasOption(std::string_view targetOpt) const
{
    return std::find(this->m_vArgs.begin(), this->m_vArgs.end(), targetOpt) !=
           this->m_vArgs.end();
}
