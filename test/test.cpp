#include "lib.h"
#include <gtest/gtest.h>

// *************************************************************************************************

TEST(Version, ValidVersion) {
    ASSERT_GT(lib::version(), 0);
}

// *************************************************************************************************
//                            CreateTupleFromVector
// *************************************************************************************************

TEST(CreateTupleFromVector, SimpleIP_1) {
    auto addr = lib::CreateTupleFromVector<lib::ip_address>::create({"127", "0", "0", "1"});
    ASSERT_TRUE(addr == std::make_tuple(127, 0, 0, 1));
}

TEST(CreateTupleFromVector, SimpleIP_2) {
    auto addr = lib::CreateTupleFromVector<lib::ip_address>::create({"0", "0", "0", "1"});
    ASSERT_TRUE(addr == std::make_tuple(0, 0, 0, 1));
}

TEST(CreateTupleFromVector, SimpleIP_3) {
    auto addr = lib::CreateTupleFromVector<lib::ip_address>::create({"255", "255", "255", "255"});
    ASSERT_TRUE(addr == std::make_tuple(255, 255, 255, 255));
}

// *************************************************************************************************
//                            CompareAll
// *************************************************************************************************

TEST(CompareAll, CompareSimple1) {
    auto addr1 = std::make_tuple(255, 255, 255, 255);
    auto addr2 = std::make_tuple(255, 255, 255, 255);
    ASSERT_TRUE(lib::CompareTuples<std::tuple_size<decltype(addr2)>::value>::CompareAll(addr1, addr2));
}

TEST(CompareAll, CompareSimple2) {
    lib::ip_address addr1 = std::make_tuple(255, 255, 255, 255);
    auto addr2 = std::make_tuple(255);
    ASSERT_TRUE(lib::CompareTuples<std::tuple_size<decltype(addr2)>::value>::CompareAll(addr1, addr2));
}

TEST(CompareAll, CompareSimple3) {
    lib::ip_address addr1 = std::make_tuple(46, 146, 255, 21);
    auto addr2 = std::make_tuple(46);
    ASSERT_TRUE(lib::CompareTuples<std::tuple_size<decltype(addr2)>::value>::CompareAll(addr1, addr2));
}

TEST(CompareAll, CompareSimple4) {
    lib::ip_address addr1 = std::make_tuple(46, 146, 255, 21);
    auto addr2 = std::make_tuple(46, 146);
    ASSERT_TRUE(lib::CompareTuples<std::tuple_size<decltype(addr2)>::value>::CompareAll(addr1, addr2));
}

