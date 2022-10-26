
#ifndef HH_UTIL_STRING_LIST_STL
#define HH_UTIL_STRING_LIST_STL

#include "util/core.hh"
#include "util/stringlist.hh"
#include "util/stringlist/format.hh"
#include "util/stringlist/ostream.hh"

#include <initializer_list>
// #include <bitset> // TODO formatter for <bitset>
#include <tuple>
// #include <variant> // TODO formatter for <variant>
// #include <optional> // TODO formatter for <optional>
#include <span>

#include <complex>

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

// #include <compare> // TODO formatter for <compare>
// #include <memory> // TODO formatter for <memory>

namespace util
{

// std::initializer_list
    template <typename C, typename T>
    struct basic_stringlist_formatter<C,std::initializer_list<T>>
        : format::basic_stringlist_iterable_formatter<C,std::initializer_list<T>>
    {};
    template <typename C, typename T>
    struct is_basic_stringlist_ostream_formattable<C,std::initializer_list<T>> : std::true_type
    {};

// std::tuple
    template <typename C, typename... Args>
    struct basic_stringlist_formatter<C,std::tuple<Args...>>
    {
        template <size_t I = 0, size_t J = sizeof...(Args)>
        void format(basic_stringlist<C>& strl, std::tuple<Args...> const& obj)
        {
            if constexpr (I == 0) strl << "["; else if (I < J) strl << ","; else strl << "]";

            if constexpr (I < J) {
                strl << std::get<I>(obj);
                format<I+1,J>(strl,obj);
            }
        }
    };
    template <typename C, typename... Args>
    struct is_basic_stringlist_ostream_formattable<C,std::tuple<Args...>> : std::true_type
    {};

// std::span
    template <typename C, typename T, size_t N>
    struct basic_stringlist_formatter<C,std::span<T,N>>
        : format::basic_stringlist_iterable_formatter<C,std::span<T,N>>
    {};
    template <typename C, typename T, size_t N>
    struct is_basic_stringlist_ostream_formattable<C,std::span<T,N>> : std::true_type
    {};

// std::complex
    template <typename C, typename T>
    struct basic_stringlist_formatter<C,std::complex<T>>
    {
        void format(basic_stringlist<C>& strl, std::complex<T> const& obj)
        {
            strl << "(" << obj.real() << "," << obj.imag() << ")";
        }
    };
    template <typename C, typename T>
    struct is_basic_stringlist_ostream_formattable<C,std::complex<T>> : std::true_type
    {};

// std::array
    template <typename C, typename T, size_t N>
    struct basic_stringlist_formatter<C,std::array<T,N>>
        : format::basic_stringlist_iterable_formatter<C,std::array<T,N>>
    {};
    template <typename C, typename T, size_t N>
    struct is_basic_stringlist_ostream_formattable<C,std::array<T,N>> : std::true_type
    {};

// std::vector
    template <typename C, typename T, typename A>
    struct basic_stringlist_formatter<C,std::vector<T,A>>
        : format::basic_stringlist_iterable_formatter<C,std::vector<T,A>>
    {};
    template <typename C, typename T, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::vector<T,A>> : std::true_type
    {};

// std::list
    template <typename C, typename T, typename A>
    struct basic_stringlist_formatter<C,std::list<T,A>>
        : format::basic_stringlist_iterable_formatter<C,std::list<T,A>>
    {};
    template <typename C, typename T, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::list<T,A>> : std::true_type
    {};

// std::forward_list
    template <typename C, typename T, typename A>
    struct basic_stringlist_formatter<C,std::forward_list<T,A>>
        : format::basic_stringlist_iterable_formatter<C,std::forward_list<T,A>>
    {};
    template <typename C, typename T, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::forward_list<T,A>> : std::true_type
    {};

// std::deque
    template <typename C, typename T, typename A>
    struct basic_stringlist_formatter<C,std::deque<T,A>>
        : format::basic_stringlist_iterable_formatter<C,std::deque<T,A>>
    {};
    template <typename C, typename T, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::deque<T,A>> : std::true_type
    {};

// std::queue
    template <typename C, typename T, typename S>
    struct basic_stringlist_formatter<C,std::queue<T,S>>
        : format::basic_stringlist_adapter_iterable_formatter<C,std::queue<T,S>>
    {};
    template <typename C, typename T, typename S>
    struct is_basic_stringlist_ostream_formattable<C,std::queue<T,S>> : std::true_type
    {};

// std::priority_queue
    template <typename C, typename T, typename S>
    struct basic_stringlist_formatter<C,std::priority_queue<T,S>>
        : format::basic_stringlist_adapter_iterable_formatter<C,std::priority_queue<T,S>>
    {};
    template <typename C, typename T, typename S>
    struct is_basic_stringlist_ostream_formattable<C,std::priority_queue<T,S>> : std::true_type
    {};

// std::stack
    template <typename C, typename T, typename S>
    struct basic_stringlist_formatter<C,std::stack<T,S>>
        : format::basic_stringlist_adapter_iterable_formatter<C,std::stack<T,S>>
    {};
    template <typename C, typename T, typename S>
    struct is_basic_stringlist_ostream_formattable<C,std::stack<T,S>> : std::true_type
    {};

// std::set
    template <typename C, typename K, typename R, typename A>
    struct basic_stringlist_formatter<C,std::set<K,R,A>>
        : format::basic_stringlist_iterable_formatter<C,std::set<K,R,A>>
    {};
    template <typename C, typename K, typename R, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::set<K,R,A>> : std::true_type
    {};

// std::multiset
    template <typename C, typename K, typename R, typename A>
    struct basic_stringlist_formatter<C,std::multiset<K,R,A>>
        : format::basic_stringlist_iterable_formatter<C,std::multiset<K,R,A>>
    {};
    template <typename C, typename K, typename R, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::multiset<K,R,A>> : std::true_type
    {};

// std::unordered_set
    template <typename C, typename K, typename H, typename P, typename A>
    struct basic_stringlist_formatter<C,std::unordered_set<K,H,P,A>>
        : format::basic_stringlist_iterable_formatter<C,std::unordered_set<K,H,P,A>>
    {};
    template <typename C, typename K, typename H, typename P, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::unordered_set<K,H,P,A>> : std::true_type
    {};

// std::unordered_multiset
    template <typename C, typename K, typename H, typename P, typename A>
    struct basic_stringlist_formatter<C,std::unordered_multiset<K,H,P,A>>
        : format::basic_stringlist_iterable_formatter<C,std::unordered_multiset<K,H,P,A>>
    {};
    template <typename C, typename K, typename H, typename P, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::unordered_multiset<K,H,P,A>> : std::true_type
    {};

// std::pair
    template <typename C, typename K, typename V>
    struct basic_stringlist_formatter<C,std::pair<K,V>>
        : format::basic_stringlist_iterable_formatter<C,std::pair<K,V>>
    {
        void format(basic_stringlist<C>& strl, std::pair<K,V> const& obj)
        {
            strl << "[" << obj.first << "," << obj.second << "]";
        }
    };
    template <typename C, typename K, typename V>
    struct is_basic_stringlist_ostream_formattable<C,std::pair<K,V>> : std::true_type
    {};

// std::map
    template <typename C, typename K, typename V, typename R, typename A>
    struct basic_stringlist_formatter<C,std::map<K,V,R,A>>
        : format::basic_stringlist_iterable_formatter<C,std::map<K,V,R,A>>
    {};
    template <typename C, typename K, typename V, typename R, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::map<K,V,R,A>> : std::true_type
    {};

// std::multimap
    template <typename C, typename K, typename V, typename R, typename A>
    struct basic_stringlist_formatter<C,std::multimap<K,V,R,A>>
        : format::basic_stringlist_iterable_formatter<C,std::multimap<K,V,R,A>>
    {};
    template <typename C, typename K, typename V, typename R, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::multimap<K,V,R,A>> : std::true_type
    {};

// std::unordered_map
    template <typename C, typename K, typename V, typename H, typename P, typename A>
    struct basic_stringlist_formatter<C,std::unordered_map<K,V,H,P,A>>
        : format::basic_stringlist_iterable_formatter<C,std::unordered_map<K,V,H,P,A>>
    {};
    template <typename C, typename K, typename V, typename H, typename P, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::unordered_map<K,V,H,P,A>> : std::true_type
    {};

// std::unordered_multimap
    template <typename C, typename K, typename V, typename H, typename P, typename A>
    struct basic_stringlist_formatter<C,std::unordered_multimap<K,V,H,P,A>>
        : format::basic_stringlist_iterable_formatter<C,std::unordered_multimap<K,V,H,P,A>>
    {};
    template <typename C, typename K, typename V, typename H, typename P, typename A>
    struct is_basic_stringlist_ostream_formattable<C,std::unordered_multimap<K,V,H,P,A>> : std::true_type
    {};

} // namespace util

#endif /* HH_UTIL_STRING_LIST_STL */
