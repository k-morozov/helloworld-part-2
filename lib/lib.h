#pragma once

#include <array>
#include <vector>
#include <iostream>

namespace lib {
    constexpr auto SIZE_IP = 4;
    using address_type = std::array<unsigned short, SIZE_IP>;

    int version();

    address_type get_address(const std::string&);

    address_type parse_address(const std::string&);

    std::vector<address_type> filter(unsigned short);

    template <typename T>
    class Filter {
    public:
        Filter(const std::vector<lib::address_type>& ip_pool) : ip_pool(ip_pool) {}

        template <typename Head, typename ...Type>
        std::vector<address_type> get(Head num, Type ... nums) {
            std::vector<address_type> result;
            for(const auto& address : ip_pool) {
                if (filter(address, num, nums...)) {
                    result.push_back(address);
                }
            }
            return result;

        }
    private:
        std::vector<lib::address_type> ip_pool;

        template <typename Head, typename ...Type>
        bool filter(const address_type& address, Head num, Type ... nums) {

            return true;
        }

        template <typename Type>
        bool filter(const address_type& address, Type num) {
            return std::find(address.begin(), address.end(),
                             num) != address.end();
        }

    };


}

std::ostream& operator<<(std::ostream& stream, const lib::address_type& ip);
