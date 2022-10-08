
#ifndef __HH_UTIL_STATISTICS_
#define __HH_UTIL_STATISTICS_

#include "core.hh"

#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

#include <numeric>
#include <algorithm>
#include <type_traits>

namespace util
{

    template <typename t_value>
    struct stats
    {
        using value_t = t_value;

        // stats::count
    public:

        template <typename Iterator>
        static size_t count(Iterator const& begin, Iterator const& end)
        {
            size_t count = 0;
            for (auto itr = begin; itr != end; ++itr) count += 1;
            return count;
        }

        template <typename Iterable>
        static size_t count(Iterable const& data)
        {
            if constexpr (util::has_std_size_v<Iterable>) {
                return std::size(data);
            } else {
                return stats::count(std::begin(data),std::end(data));
            }
        }

        // stats::sum
    public:

        template <typename Iterator>
        static value_t sum(Iterator const& begin, Iterator const& end)
        {
            return std::accumulate(begin,end,value_t{});
        }

        template <typename Iterable>
        static value_t sum(Iterable const& data)
        {
            return stats::sum(std::begin(data),std::end(data));
        }

        // stats::min
    public:

        template <typename Iterator>
        static value_t min(Iterator const& begin, Iterator const& end)
        {
            return (value_t)*std::min_element(begin,end);
        }

        template <typename Iterable>
        static value_t min(Iterable const& data)
        {
            return stats::min(std::begin(data),std::end(data));
        }

        // stats::max
    public:

        template <typename Iterator>
        static value_t max(Iterator const& begin, Iterator const& end)
        {
            return (value_t)*std::max_element(begin,end);
        }

        template <typename Iterable>
        static value_t max(Iterable const& data)
        {
            return stats::max(std::begin(data),std::end(data));
        }

        // stats::range
    public:

        template <typename Iterator>
        static value_t range(Iterator const& begin, Iterator const& end)
        {
            Iterator min = begin, max = begin;

            for (Iterator itr = begin; itr != end; ++itr)
            {
                if (*min > *itr) min = itr;
                if (*max < *itr) max = itr;
            }
            return (value_t)*max - (value_t)*min;
        }

        template <typename Iterable>
        static value_t range(Iterable const& data)
        {
            return stats::range(std::begin(data),std::end(data));
        }

        // stat::mode
    public:

        template <typename Iterator>
        static value_t mode(Iterator const& begin, Iterator const& end)
        {
            using data_t = std::iterator_traits<Iterator>::value_type;
            using count_map_t = std::conditional_t<util::is_std_hashable_v<data_t>,
                std::unordered_map<data_t,size_t>, std::map<data_t,size_t> >;
            count_map_t count_map;

            for (auto itr = begin; itr != end; ++itr)
            {
                count_map[*itr] += 1;
            }

            auto max = std::max_element(count_map.begin(),count_map.end(),
                [](auto const& p1, auto const& p2)
            {
                return p1.second < p2.second;
            });
            return (value_t)max->first;
        }

        template <typename Iterable>
        static value_t mode(Iterable const& data)
        {
            return stats::mode(std::begin(data),std::end(data));
        }

        // stats::median
    private:

        template <typename Iterator>
        static value_t __median(Iterator const& begin, Iterator const& end, size_t count)
        {
            using data_t = std::iterator_traits<Iterator>::value_type;
            size_t size = 1+count/2;
            std::vector<data_t> min_heap (begin,begin+size);

            auto sift_down = [&](size_t index)
            {
                size_t size = min_heap.size();
                for (size_t i = index, j = i; true; i = j)
                {
                    size_t l = 2*i+1, r = 2*i+2;

                    if (l >= size) break; // i is a leaf node
                    j = (r >= size) ? l : (min_heap[l] < min_heap[r]) ? l : r;
                    if (min_heap[i] > min_heap[j]) std::swap(min_heap[i],min_heap[j]);
                }
            };
            for (size_t i = size-1; i < size; --i) sift_down(i);

            for (auto itr = begin+size; itr != end; ++itr)
            {
                if (*itr < min_heap[0]) continue;
                min_heap[0] = *itr; sift_down(0);
            }

            return (count % 2 == 1) ? (value_t)min_heap[0]
                : ((value_t)min_heap[0] + (value_t)std::min(min_heap[1],min_heap[2])) / 2;
        }

    public:

        template <typename Iterator>
        static value_t median(Iterator const& begin, Iterator const& end)
        {
            return stats::__median(begin,end,stats::count(begin,end));
        }

        template <typename Iterable>
        static value_t median(Iterable const& data)
        {
            return stats::__median(std::begin(data),std::end(data),stats::count(data));
        }

        // stats::mean
    public:

        template <typename Iterator>
        static value_t mean(Iterator const& begin, Iterator const& end)
        {
            using data_t = std::iterator_traits<Iterator>::value_type;
            data_t sum = data_t{}; size_t count = 0;

            for (Iterator itr = begin; itr != end; ++itr)
            {
                sum += *itr; count += 1;
            }
            return (value_t)sum / count;
        }

        template <typename Iterable>
        static value_t mean(Iterable const& data)
        {
            return stats::mean(std::begin(data),std::end(data));
        }

        // stats::stdev
    public:

        // template <typename Iterator>
        // static value_t stdev(Iterator const& begin, Iterator const& end)
        // {
        //     // TODO stats::stdev
        // }

        // template <typename Iterable>
        // static value_t stdev(Iterable const& data)
        // {
        //     // TODO stats::stdev
        // }

        // stats::quartiles
    public:

        // template <typename Iterator>
        // static auto quartiles(Iterator const& begin, Iterator const& end)
        //     -> std::vector<value_t>
        // {
        //     // TODO stats::quartiles
        // }

        // template <typename Iterable>
        // static auto quartiles(Iterable const& data)
        //     -> std::vector<value_t>
        // {
        //     // TODO stats::quartiles
        // }

        // stats::outliers
    public:

        // template <typename Iterator>
        // static auto outliers(Iterator const& begin, Iterator const& end)
        //     -> std::vector<std::iterator_traits<Iterator>::value_type>
        // {
        //     // TODO stats::outliers
        // }

        // template <typename Iterable>
        // static auto outliers(Iterable const& data)
        //     -> std::vector<util::std_iterable_element_t<iterable>>
        // {
        //     // TODO stats::outliers
        // }

    };

    // source: https://www.calculatorsoup.com/calculators/statistics/mean-median-mode.php
    // TODO: remove me!

} // namespace util

#endif /* __HH_UTIL_STATISTICS_ */
