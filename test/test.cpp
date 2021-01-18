#include "lib.h"
#include <gtest/gtest.h>

TEST(Version, ValidVersion) {
    ASSERT_GT(lib::version(), 0);
}

TEST(CreateIP, SimpleIP_1) {
    auto addr = lib::CreateTupleFromVector<lib::ip_address>::create({"127", "0", "0", "1"});
    ASSERT_TRUE(addr == std::make_tuple(127, 0, 0, 1));
}

TEST(CreateIP, SimpleIP_2) {
    auto addr = lib::CreateTupleFromVector<lib::ip_address>::create({"0", "0", "0", "1"});
    ASSERT_TRUE(addr == std::make_tuple(0, 0, 0, 1));
}

TEST(CreateIP, SimpleIP_3) {
    auto addr = lib::CreateTupleFromVector<lib::ip_address>::create({"255", "255", "255", "255"});
    ASSERT_TRUE(addr == std::make_tuple(255, 255, 255, 255));
}
