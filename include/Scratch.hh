
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

#include <bitset>
#include <initializer_list>
#include <tuple>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>
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
//  Print Operator Overloads for Three-Way Comparison
/* ************************************************************************** */

template <typename C>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::strong_ordering const& ord)
{
    if (ord == std::strong_ordering::equal)         return ost << "strong_ordering::equal";
    if (ord == std::strong_ordering::equivalent)    return ost << "strong_ordering::equivalent";
    if (ord == std::strong_ordering::less)          return ost << "strong_ordering::less";
    if (ord == std::strong_ordering::greater)       return ost << "strong_ordering::greater";
    return ost << "strong_ordering";
}

template <typename C>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::weak_ordering const& ord)
{
    if (ord == std::weak_ordering::equivalent)  return ost << "weak_ordering::equivalent";
    if (ord == std::weak_ordering::less)        return ost << "weak_ordering::less";
    if (ord == std::weak_ordering::greater)     return ost << "weak_ordering::greater";
    return ost << "weak_ordering";
}

template <typename C>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::partial_ordering const& ord)
{
    if (ord == std::partial_ordering::equivalent)   return ost << "partial_ordering::equivalent";
    if (ord == std::partial_ordering::less)         return ost << "partial_ordering::less";
    if (ord == std::partial_ordering::greater)      return ost << "partial_ordering::greater";
    if (ord == std::partial_ordering::unordered)    return ost << "partial_ordering::unordered";
    return ost << "partial_ordering";
}


/* ************************************************************************** */
//  Print Operator Overloads for STL Containers
/* ************************************************************************** */

namespace util
{

    template <typename C>
    class StringList;

    template <typename C, typename ForwardIterable>
    StringList<C> make_stringlist(ForwardIterable const& data);

    template <typename C, typename... Args>
    StringList<C> make_stringlist(std::tuple<Args...> const& tuple);

} // namespace util

template <typename C, size_t N>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::bitset<N> const& data)
{
    // TODO
    return ost << "operator<< undefined for std::bitset";
}

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::initializer_list<T> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename... Args>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::tuple<Args...> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, size_t N>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::array<T,N> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::vector<T,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::list<T,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::forward_list<T,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::deque<T,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, typename S>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::queue<T,S> const& data)
{
    // TODO
    return ost << "operator<< undefined for std::queue";
}

template <typename C, typename T, typename S, typename R>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::priority_queue<T,S,R> const& data)
{
    // TODO
    return ost << "operator<< undefined for std::priority_queue";
}

template <typename C, typename T, typename S>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::stack<T,S> const& data)
{
    // TODO
    return ost << "operator<< undefined for std::stack";
}

template <typename C, typename T, typename R>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::set<T,R> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, typename H, typename P, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::unordered_set<T,H,P,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, typename H, typename P, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::unordered_multiset<T,H,P,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename K, typename V>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::pair<K,V> const& data)
{
    return ost << '[' << data.first << "," << data.second << ']';
}

template <typename C, typename K, typename V, typename R, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::map<K,V,R,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename K, typename V, typename H, typename P, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::unordered_map<K,V,H,P,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename K, typename V, typename H, typename P, typename A>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::unordered_multimap<K,V,H,P,A> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, size_t N>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::span<T,N> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

#include "StringList.hh"

#endif /* __HH_SCRATCH */
