
#ifndef __HH_SCRATCH_PRINTING_
#define __HH_SCRATCH_PRINTING_

#include "Util.hh"

// #include <complex> // TODO printing for <complex>
// #include <optional> // TODO printing for <optional>
// #include <variant> // TODO printing for <variant>

#include <compare>

#include <initializer_list>
#include <bitset>
#include <tuple>
#include <span>

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

// #include <memory> // TODO printing for <memory>

#include <ostream> // print adapter

// forward-declare "StringList.hh" here, and include it at the end
// so that operator<< works with nested containers.
namespace util
{

    template <typename C>
    class BasicStringList;

    template <typename C, typename ForwardIterable>
        requires util::is_std_iterable_v<ForwardIterable>
    BasicStringList<C> make_stringlist(ForwardIterable const& data);

    template <typename C, typename... Args>
    BasicStringList<C> make_stringlist(std::tuple<Args...> const& tuple);

} // namespace util

// default-printing for all types with a `print(std::basic_ostream)` function.
template <typename C, typename Printable>
    requires requires (std::basic_ostream<C>& ost, Printable& data) { data.print(ost); }
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, Printable const& data)
{
    data.print(ost); return ost;
}

/* ************************************************************************** */
//  Three-Way Comparison
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
//  STL Containers
/* ************************************************************************** */

template <typename C, typename T>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::initializer_list<T> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, size_t N>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::bitset<N> const& data)
{
    // TODO
    return ost << "operator<< undefined for std::bitset";
}

template <typename C, typename... Args>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::tuple<Args...> const& data)
{
    return ost << '[' << util::make_stringlist<C>(data).to_string(",") << ']';
}

template <typename C, typename T, size_t N>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::span<T,N> const& data)
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
    return ost << util::adapters<std::queue<T,S>>::get(data);
}

template <typename C, typename T, typename S, typename R>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::priority_queue<T,S,R> const& data)
{
    return ost << util::adapters<std::priority_queue<T,S,R>>::get(data);
}

template <typename C, typename T, typename S>
inline std::basic_ostream<C>&
operator<<(std::basic_ostream<C>& ost, std::stack<T,S> const& data)
{
    return ost << util::adapters<std::stack<T,S>>::get(data);
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

#include "StringList.hh"

#endif /* __HH_SCRATCH_PRINTING_ */
