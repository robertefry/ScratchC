
#include "util/stringlist.hh"

#include <sstream>

#include <gtest/gtest.h>

TEST(UTIL_STRINGLIST,STD_OSTREAM)
{
    util::stringlist strl;
    strl << "abc" << 123;

    std::stringstream ss;
    ss << strl;
    EXPECT_EQ(ss.str(),"abc123");
}

TEST(UTIL_STRINGLIST,TO_STRING)
{
    util::stringlist strl;
    strl << "abc" << 123;
    EXPECT_EQ((std::string)strl,"abc123");
    EXPECT_EQ(strl.to_string(),"abc123");
    EXPECT_EQ(strl.to_string(" "),"abc 123");
}

TEST(UTIL_STRINGLIST,CUSTOM_TYPES)
{
    {
        struct to_stringlist_t
        {
            void to_stringlist(util::stringlist& strl) { strl << "x"; }
        };
        util::stringlist strl;

        to_stringlist_t tsl;
        strl << tsl;
        strl << std::move(tsl);

        // // impossible to call these
        // to_stringlist_t const tsl_c;
        // strl << tsl_c;
        // strl << std::move(tsl_c);

        EXPECT_EQ(strl.to_string(),"xx");
    }
    {
        struct to_stringlist_t
        {
            void to_stringlist(util::stringlist& strl) const { strl << "y"; }
        };
        util::stringlist strl;

        to_stringlist_t tsl;
        strl << tsl;
        strl << std::move(tsl);

        to_stringlist_t const tsl_c;
        strl << tsl_c;
        strl << std::move(tsl_c);

        EXPECT_EQ(strl.to_string(),"yyyy");
    }
    {
        struct to_stringlist_t
        {
            void to_stringlist(util::stringlist& strl) { strl << "x"; }
            void to_stringlist(util::stringlist& strl) const { strl << "y"; }
        };
        util::stringlist strl;

        to_stringlist_t tsl;
        strl << tsl;
        strl << std::move(tsl);

        to_stringlist_t const tsl_c;
        strl << tsl_c;
        strl << std::move(tsl_c);

        EXPECT_EQ(strl.to_string(),"xxyy");
    }
}
