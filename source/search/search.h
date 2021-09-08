#pragma once
#include <string>

namespace cog::search {
    std::string left_pad(std::string input, std::size_t length, char filler = ' ');
}