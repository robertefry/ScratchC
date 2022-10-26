
#ifndef HH_UTIL_LOGGING
#define HH_UTIL_LOGGING

#include "util/stringlist/ostream.hh"

#include <fmt/core.h>
#include <fmt/ostream.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

/* ************************************************************************** */
// util::log
/* ************************************************************************** */

namespace util
{

    inline auto logger()
    {
        static auto logger = []()
        {
            auto logger = spdlog::stdout_color_mt("util");
            logger->set_pattern("[%t] %v");
            return logger;
        }();
        return logger;
    }

    template <typename... Args>
    void log(fmt::format_string<Args...> format, Args&&... args)
    {
        logger()->info(fmt::format(format,std::forward<Args>(args)...));
    }

} // namespace util

template <typename C, typename T>
    requires util::is_basic_stringlist_ostream_formattable<C,T>::value
struct fmt::formatter<T,C> : fmt::basic_ostream_formatter<C>
{};

#endif /* HH_UTIL_LOGGING */
