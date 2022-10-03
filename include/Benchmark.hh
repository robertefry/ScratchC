
#ifndef __HH_UTIL_BENCHMARK_
#define __HH_UTIL_BENCHMARK_

#include <cstddef>
#include <chrono>

#include <vector>

namespace util
{

    template <typename t_func, typename... t_args>
    auto benchmark(size_t count, t_func const& func, t_args&&... args)
    {
        using clock = std::chrono::high_resolution_clock;
        std::vector<float> times; times.reserve(count);

        while (count-- != 0)
        {
            auto now = clock::now();
            func(args...);
            times.push_back((clock::now()-now).count());
        }
        return times;
    }

} // namespace util

#endif /* __HH_UTIL_BENCHMARK_ */
