
#ifndef __HH_UTIL_STRING_LIST_OSTREAM_
#define __HH_UTIL_STRING_LIST_OSTREAM_

#include "util/stringlist.hh"

#include <ostream>
#include <type_traits>

namespace util
{

    template <typename C, typename T>
    struct is_basic_stringlist_ostream_formattable : std::false_type
    {};

    template <typename T> using is_stringlist_ostream_formattable = is_basic_stringlist_ostream_formattable<char,T>;
    template <typename T> using is_wstringlist_ostream_formattable = is_basic_stringlist_ostream_formattable<wchar_t,T>;

} // namespace util

template <typename C, typename T>
    requires util::has_to_stringlist<C,T>
struct util::is_basic_stringlist_ostream_formattable<C,T> : std::true_type
{};

template <typename C, typename T>
    requires util::is_basic_stringlist_ostream_formattable<C,T>::value
std::basic_ostream<C>& operator<<(std::basic_ostream<C>& ost, T const& t)
{
    util::basic_stringlist<C> strl;
    strl << t;
    return ost << strl.to_string();
}

#endif /* __HH_UTIL_STRING_LIST_OSTREAM_ */
