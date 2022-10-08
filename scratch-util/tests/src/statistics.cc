
#include "util/statistics.hh"
#include "util/stringlist/ostream.hh"

#include <sstream>

#include <gtest/gtest.h>

std::vector<int> make_random_vector(size_t size, int min, int max)
{
    std::vector<int> vec; vec.reserve(size);
    for (size_t i = 0; i < size; ++i) vec.push_back(min+rand()%(max-min));
    return vec;
}

static struct seed_rng_t { seed_rng_t() { srand(time(NULL)); } } seed_rng;

TEST(UTIL_STATISTICS,COUNT)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    size_t count = vec.size();
    EXPECT_EQ(util::stats<float>::count(vec.begin(),vec.end()),count);
    EXPECT_EQ(util::stats<float>::count(vec),count);
}

TEST(UTIL_STATISTICS,SUM)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    float sum = std::accumulate(vec.begin(),vec.end(),0.0f);
    EXPECT_EQ(util::stats<float>::sum(vec.begin(),vec.end()),sum);
    EXPECT_EQ(util::stats<float>::sum(vec),sum);
}

TEST(UTIL_STATISTICS,MIN)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    float min = *std::min_element(vec.begin(),vec.end());
    EXPECT_EQ(util::stats<float>::min(vec.begin(),vec.end()),min);
    EXPECT_EQ(util::stats<float>::min(vec),min);
}

TEST(UTIL_STATISTICS,MAX)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    float max = *std::max_element(vec.begin(),vec.end());
    EXPECT_EQ(util::stats<float>::max(vec.begin(),vec.end()),max);
    EXPECT_EQ(util::stats<float>::max(vec),max);
}

TEST(UTIL_STATISTICS,RANGE)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    float min = *std::min_element(vec.begin(),vec.end());
    float max = *std::max_element(vec.begin(),vec.end());
    EXPECT_EQ(util::stats<float>::range(vec.begin(),vec.end()),max-min);
    EXPECT_EQ(util::stats<float>::range(vec),max-min);
}

TEST(UTIL_STATISTICS,MODE)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    float mode = [&]()
    {
        std::unordered_map<int,size_t> counts;
        for (size_t i = 0; i < vec.size(); ++i) counts[vec[i]] += 1;
        return std::max_element(counts.begin(),counts.end(),
            [](auto a, auto b){ return a.second < b.second; })->first;
    }();
    EXPECT_EQ(util::stats<float>::mode(vec.begin(),vec.end()),mode);
    EXPECT_EQ(util::stats<float>::mode(vec),mode);
}

TEST(UTIL_STATISTICS,MEDIAN)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    float median = [&]()
    {
        std::vector<int> sorted = vec; std::sort(sorted.begin(),sorted.end());
        if (vec.size() % 2 == 1) return sorted[vec.size()/2];
        return (sorted[vec.size()/2] + sorted[1+vec.size()/2]) / 2;
    }();
    EXPECT_EQ(util::stats<float>::median(vec.begin(),vec.end()),median);
    EXPECT_EQ(util::stats<float>::median(vec),median);
}

TEST(UTIL_STATISTICS,MEAN)
{
    std::vector<int> vec = make_random_vector(16+rand()%16,16,32);
    float mean = std::accumulate(vec.begin(),vec.end(),0) / (float)vec.size();
    EXPECT_EQ(util::stats<float>::mean(vec.begin(),vec.end()),mean);
    EXPECT_EQ(util::stats<float>::mean(vec),mean);
}
