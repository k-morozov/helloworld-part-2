#pragma once

#include <array>
#include <iostream>

namespace lib {
    constexpr auto SIZE_IP = 4;
    using address_type = std::array<unsigned short, SIZE_IP>;



    int version();

    address_type get_address(const std::string&);

    address_type parse_address(const std::string&);
}

std::ostream& operator<<(std::ostream& stream, const lib::address_type& ip);
