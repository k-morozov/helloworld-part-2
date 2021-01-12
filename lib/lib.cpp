#include "lib.h"

#include "config/version.h"
#include <cassert>

namespace lib {

int version() {
    return PROJECT_VERSION_PATCH;
}

address_type get_address(const std::string& str) {
    std::string::size_type end = str.find_first_of('\t');

    return parse_address(str.substr(0, end));
}

address_type parse_address(const std::string& str) {
    address_type address;
    std::size_t count = 0;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of('.');

    while(stop != std::string::npos && count < SIZE_IP) {
        int value = 0;
        try {
            value = std::stoi(str.substr(start, stop - start));
        }  catch (std::exception &ex) {
            std::cerr << __PRETTY_FUNCTION__ << ": " << value << std::endl;
            std::cerr << ex.what() << std::endl;
            value = 0;
        }
        assert(value < 256);
        address[count] = static_cast<unsigned short>(value);

        count++;
        start = stop + 1;
        stop = str.find_first_of('.', start);
    }
    if (stop == std::string::npos && count < SIZE_IP) {
        address[count] = static_cast<unsigned short>(std::stoi(str.substr(start, stop - start)));
        count++;
    }
    assert(count == SIZE_IP);

    return address;
}

}

std::ostream& operator<<(std::ostream& stream, const lib::address_type& ip) {
    stream << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3];
    return stream;
}

