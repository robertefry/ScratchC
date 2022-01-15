
#ifndef __HH_SCRATCH
#define __HH_SCRATCH

#ifdef __GNUC__
#define SC_GetFunctionName() __PRETTY_FUNCTION__
#else
#define SC_GetFunctionName() "<funcname>"
#endif


#include <iostream>
#include <iomanip>
#include <cstdio>

#include <cstring>
#include <string>
#include <sstream>
#include <regex>

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <climits>
#include <cmath>
#include <ctime>

#include <complex>

#include <optional>
#include <variant>
#include <tuple>
#include <bitset>

#include <initializer_list>
#include <array>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <span>

#include <type_traits>
#include <concepts>
#include <compare>
#include <limits>
#include <utility>
#include <numeric>
#include <algorithm>
#include <functional>
#include <memory>
#include <chrono>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


/* ************************************************************************** */
//  Lifetime Tracker
/* ************************************************************************** */

struct LifetimeTracker
{
    LifetimeTracker()
    {
        std::cout << SC_GetFunctionName() << "\n";
    }
    LifetimeTracker(int)
    {
        std::cout << SC_GetFunctionName() << "\n";
    }
    virtual ~LifetimeTracker()
    {
        std::cout << SC_GetFunctionName() << "\n";
    }
    LifetimeTracker(LifetimeTracker const&)
    {
        std::cout << SC_GetFunctionName() << "\n";
    }
    LifetimeTracker(LifetimeTracker&&)
    {
        std::cout << SC_GetFunctionName() << "\n";
    }
    LifetimeTracker& operator=(LifetimeTracker const&)
    {
        std::cout << SC_GetFunctionName() << "\n";
        return *this;
    }
    LifetimeTracker& operator=(LifetimeTracker&&)
    {
        std::cout << SC_GetFunctionName() << "\n";
        return *this;
    }
};


/* ************************************************************************** */
//  Utility StringList
/* ************************************************************************** */

#include "StringList.hh"

namespace util
{

    template <typename C = char, typename ForwardIterable>
    StringList<C> make_stringlist(ForwardIterable const& data)
    {
        StringList<C> list;

        for (auto itr = data.begin(); itr != data.end(); ++itr)
        {
            list << *itr;
        }
        return list;
    }

    template <typename C = char, size_t I, size_t J, typename... Args>
    StringList<C> make_stringlist(std::tuple<Args...> const& tuple)
    {
        StringList<C> list;

        if constexpr (I < J)
        {
            list << std::get<I>(tuple);
            list.push_back(make_stringlist<C,I+1,J>(tuple));
        }
        return list;
    }

    template <typename C = char, typename... Args>
    StringList<C> make_stringlist(std::tuple<Args...> const& tuple)
    {
        return make_stringlist<C,0,sizeof...(Args),Args...>(tuple);
    }

} // namespace util


/* ************************************************************************** */
//  Print Operator Overloads for Three-Way Comparison
/* ************************************************************************** */

template <typename C>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::strong_ordering& ord)
{
    if (ord == std::strong_ordering::equal)         return ost << "strong_ordering::equal";
    if (ord == std::strong_ordering::equivalent)    return ost << "strong_ordering::equivalent";
    if (ord == std::strong_ordering::less)          return ost << "strong_ordering::less";
    if (ord == std::strong_ordering::greater)       return ost << "strong_ordering::greater";
    return ost << "strong_ordering::[?]";
}

template <typename C>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::weak_ordering& ord)
{
    if (ord == std::weak_ordering::equivalent)  return ost << "weak_ordering::equivalent";
    if (ord == std::weak_ordering::less)        return ost << "weak_ordering::less";
    if (ord == std::weak_ordering::greater)     return ost << "weak_ordering::greater";
    return ost << "weak_ordering::[?]";
}

template <typename C>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::partial_ordering& ord)
{
    if (ord == std::partial_ordering::equivalent)   return ost << "partial_ordering::equivalent";
    if (ord == std::partial_ordering::less)         return ost << "partial_ordering::less";
    if (ord == std::partial_ordering::greater)      return ost << "partial_ordering::greater";
    if (ord == std::partial_ordering::unordered)    return ost << "partial_ordering::unordered";
    return ost << "partial_ordering::[?]";
}


/* ************************************************************************** */
//  Print Operator Overloads for STL Containers
/* ************************************************************************** */

template <typename C, typename... Args>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::tuple<Args...>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::initializer_list<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, size_t N>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::array<T,N>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::vector<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::list<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::queue<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::set<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::unordered_set<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::unordered_multiset<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename K, typename V>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::map<K,V>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename K, typename V>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::unordered_map<K,V>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename K, typename V>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::unordered_multimap<K,V>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::span<T>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, size_t N>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, const std::span<T,N>& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

#endif /* __HH_SCRATCH */
