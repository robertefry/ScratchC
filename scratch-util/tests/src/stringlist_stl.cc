
#include "util/stringlist.hh"
#include "util/stringlist/stl.hh"

#include <gtest/gtest.h>

// std::initializer_list
TEST(UTIL_STRINGLIST,STL_INITIALIZER_LIST)
{
    util::stringlist strl;

    std::initializer_list<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::bitset

// std::tuple
TEST(UTIL_STRINGLIST,STL_TUPLE)
{
    util::stringlist strl;

    std::tuple<int,float,std::string> obj {42,3.14f,"foobar"};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[42,3.140000,foobar]");
}

// std::span
TEST(UTIL_STRINGLIST,STL_SPAN)
{
    util::stringlist strl;

    std::vector<int> vec = {1,2,3,4,5,6,7,8,9};
    std::span<int,3> obj (vec.begin()+2,vec.begin()+5);
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[3,4,5]");
}

// std::pair
TEST(UTIL_STRINGLIST,STL_COMPLEX)
{
    util::stringlist strl;

    std::complex<int> obj {3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"(3,4)");
}

// std::array
TEST(UTIL_STRINGLIST,STL_ARRAY)
{
    util::stringlist strl;

    std::array<int,4> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::vector
TEST(UTIL_STRINGLIST,STL_VECTOR)
{
    util::stringlist strl;

    std::vector<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::list
TEST(UTIL_STRINGLIST,STL_LIST)
{
    util::stringlist strl;

    std::list<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::forward_list
TEST(UTIL_STRINGLIST,STL_FORWARD_LIST)
{
    util::stringlist strl;

    std::forward_list<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::deque
TEST(UTIL_STRINGLIST,STL_DEQUE)
{
    util::stringlist strl;

    std::deque<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::queue
TEST(UTIL_STRINGLIST,STL_QUEUE)
{
    util::stringlist strl;

    std::queue<int> obj; obj.push(1); obj.push(2); obj.push(3);
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3]");
}

// std::priority_queue
TEST(UTIL_STRINGLIST,STL_PRIORITY_QUEUE)
{
    util::stringlist strl;

    std::priority_queue<int> obj; obj.push(1); obj.push(2); obj.push(3);
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[3,1,2]");
}

// std::stack
TEST(UTIL_STRINGLIST,STL_STACK)
{
    util::stringlist strl;

    std::stack<int> obj; obj.push(1); obj.push(2); obj.push(3);
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3]");
}

// std::set
TEST(UTIL_STRINGLIST,STL_SET)
{
    util::stringlist strl;

    std::set<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::multiset
TEST(UTIL_STRINGLIST,STL_MULTISET)
{
    util::stringlist strl;

    std::multiset<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[1,2,3,4]");
}

// std::unordered_set
TEST(UTIL_STRINGLIST,STL_UNORDERED_SET)
{
    util::stringlist strl;

    std::unordered_set<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[4,3,2,1]");
}

// std::unordered_multiset
TEST(UTIL_STRINGLIST,STL_UNORDERED_MULTISET)
{
    util::stringlist strl;

    std::unordered_multiset<int> obj {1,2,3,4};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[4,3,2,1]");
}

// std::pair
TEST(UTIL_STRINGLIST,STL_PAIR)
{
    util::stringlist strl;

    std::pair<int,float> obj {42,3.14};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[42,3.140000]");
}

// std::map
TEST(UTIL_STRINGLIST,STL_MAP)
{
    util::stringlist strl;

    std::map<int,float> obj {{42,3.14},{69,4.20f}};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[[42,3.140000],[69,4.200000]]");
}

// std::multimap
TEST(UTIL_STRINGLIST,STL_MULTIMAP)
{
    util::stringlist strl;

    std::multimap<int,float> obj {{42,3.14},{69,4.20f}};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[[42,3.140000],[69,4.200000]]");
}

// std::unordered_map
TEST(UTIL_STRINGLIST,STL_UNORDERED_MAP)
{
    util::stringlist strl;

    std::unordered_map<int,float> obj {{42,3.14},{69,4.20f}};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[[69,4.200000],[42,3.140000]]");
}

// std::unordered_multimap
TEST(UTIL_STRINGLIST,STL_UNORDERED_MULTIMAP)
{
    util::stringlist strl;

    std::unordered_multimap<int,float> obj {{42,3.14},{69,4.20f}};
    strl << obj;
    EXPECT_EQ(strl.to_string(),"[[69,4.200000],[42,3.140000]]");
}
