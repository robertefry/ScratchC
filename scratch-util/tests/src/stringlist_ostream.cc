
#include "util/stringlist.hh"
#include "util/stringlist/ostream.hh"
#include "util/stringlist/stl.hh"

#include <sstream>

#include <gtest/gtest.h>

struct test_formattable_t
{};
template <typename C>
struct util::basic_stringlist_formatter<C,test_formattable_t>
{
    void format(basic_stringlist<C>& strl, test_formattable_t const&)
    {
        strl << "test_formattable_t";
    }
};
template <typename C>
struct util::is_basic_stringlist_ostream_formattable<C,test_formattable_t> : std::true_type
{};

struct test_to_stringlist_t
{
    template <typename C>
    void to_stringlist(util::basic_stringlist<C>& strl) const { strl << "test_to_stringlist_t"; }
};

TEST(UTIL_STRINGLIST,OSTREAM_FORMATTABLE)
{
    test_formattable_t test_formattable;
    {
        std::ostringstream oss;
        oss << test_formattable;
        EXPECT_EQ(oss.str(),"test_formattable_t");
    }

    test_to_stringlist_t test_to_stringlist;
    {
        std::ostringstream oss;
        oss << test_to_stringlist;
        EXPECT_EQ(oss.str(),"test_to_stringlist_t");
    }
}
