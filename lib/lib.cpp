#include "lib.h"

#include "config/version.h"
#include <cassert>

namespace lib {

int version() {
    return PROJECT_VERSION_PATCH;
}

void IPAddressPool::insert(const std::string& address_str) {
    auto address = split(address_str, '.');
    auto address_tuple = CreateTupleFromVector<ip_address>::create(address);
    insert(address_tuple);
}

void IPAddressPool::insert(const ip_address& address) {
    ++ip_pool[address];
}

std::vector<std::string> IPAddressPool::split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void IPAddressPool::print(std::ostream& ostream, std::function<bool(ip_address)> filter) {
    for(const auto& value : ip_pool) {
        if(!filter(value.first)) {
            continue;
        }

        for(int i = 0; i < value.second; i++) {
            PrintTuple(ostream, value.first);
            ostream << std::endl;
        }
    }
}
}

