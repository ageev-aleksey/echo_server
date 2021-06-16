#include <gtest/gtest.h>

#include "server/Session.h"

#include <vector>
#include <string>


std::vector<char> makeVector(const std::string str) {
    std::vector<char> ret;
    ret.reserve(str.size());
    for(const auto &el : str) {
        ret.push_back(el);
    }
    return ret;
}

TEST(SessionTest, a) {
    CommandBuffer b;

    b.push(makeVector("hello world;"));
    b.push(makeVector("welcome"));
    b.push(makeVector(" to the city;"));
    ASSERT_EQ(b.getCommandsNum(), 2);
    ASSERT_EQ(b.getCommand(0), makeVector("hello world;"));
    ASSERT_EQ(b.getCommand(1), makeVector("welcome to the city;"));
}

::testing::Test