#pragma once

#include <string_view>
#include <vector>

class CmdParser
{
public:
    CmdParser(const char** argv, int argc);
    ~CmdParser() = default;

    std::string_view GetOption(std::string_view targetOpt) const;
    std::string_view GetByIndex(size_t targetIndex) const;
    bool HasOption(std::string_view targetOpt) const;

    inline size_t GetArgsNum() const noexcept;

private:
    std::vector<std::string_view> m_vArgs;
};

inline size_t CmdParser::GetArgsNum() const noexcept
{
    return this->m_vArgs.size();
}
