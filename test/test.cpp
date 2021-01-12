#include "lib.h"
#include <gtest/gtest.h>

TEST(Version, ValidVersion) {
    ASSERT_GT(lib::version(), 0);
}

TEST(ParserAddress, GetAddressFromSimpleStr) {
    lib::address_type address{127, 0, 0, 1};
    ASSERT_TRUE(address == lib::parse_address("127.0.0.1"));
}

TEST(ParserAddress, GetFullAddressFromStr) {
    lib::address_type address{127, 0, 0, 1};
    ASSERT_TRUE(address == lib::get_address("127.0.0.1\t asd \t\n"));
}
