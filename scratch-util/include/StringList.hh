
#ifndef __HH_UTIL_STRING_LIST
#define __HH_UTIL_STRING_LIST

#include "Util.hh"
#include "Printing.hh"

#include <list>
#include <tuple>

#include <string>
#include <sstream>
#include <iosfwd>

/* ************************************************************************** */
//  Definition
/* ************************************************************************** */

namespace util
{

    template <typename C = char>
    class StringList
    {
    public:
        explicit StringList() = default;
        virtual ~StringList() = default;

    public:
        StringList<C>& push_back(std::basic_string<C> const&);
        StringList<C>& push_back(std::basic_string<C>&&);
        StringList<C>& push_back(StringList<C> const&);
        StringList<C>& push_back(StringList<C>&&);

        template <typename Tp>
        StringList<C>& operator<<(Tp const&);

        std::basic_string<C> to_string(std::basic_string<C> const& delim = " ") const;

    private:
        std::list<std::basic_string<C>> m_List{};
    };

} // namespace util

/* ************************************************************************** */
//  Helper Functions
/* ************************************************************************** */

namespace util
{

    template <typename C = char, typename ForwardIterable>
        requires util::is_std_iterable_v<ForwardIterable>
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
//  Implementation
/* ************************************************************************** */

namespace util
{

    template <typename C>
    StringList<C>& StringList<C>::push_back(std::basic_string<C> const& string)
    {
        m_List.push_back(string);
        return *this;
    }

    template <typename C>
    StringList<C>& StringList<C>::push_back(std::basic_string<C>&& string)
    {
        m_List.push_back(std::move(string));
        return *this;
    }

    template <typename C>
    StringList<C>& StringList<C>::push_back(StringList<C> const& stringlist)
    {
        for (std::basic_string<C> const& string : stringlist.m_List)
        {
            m_List.push_back(string);
        }
        return *this;
    }

    template <typename C>
    StringList<C>& StringList<C>::push_back(StringList<C>&& stringlist)
    {
        for (std::basic_string<C>& string : stringlist.m_List)
        {
            m_List.push_back(std::move(string));
        }
        return *this;
    }

    template <typename C>
    template <typename Tp>
    StringList<C>& StringList<C>::operator<<(Tp const& obj)
    {
        std::basic_ostringstream<C> oss;
        oss << obj;
        push_back(oss.str());
        return *this;
    }

    template <typename C>
    std::basic_string<C> StringList<C>::to_string(std::basic_string<C> const& delim) const
    {
        size_t size = 0;
        for (auto const& string : m_List) {
            size += string.size();
        }
        if (m_List.size()) size += delim.size() * (m_List.size()-1);

        std::basic_string<C> result;
        result.reserve(size);

        if (m_List.size())
        {
            auto itr = m_List.begin();
            result += *itr;

            for (++itr; itr != m_List.end(); ++itr)
            {
                result += delim;
                result += *itr;
            }
        }

        return result;
    }

} // namespace util

/* ************************************************************************** */
//  Global Operators
/* ************************************************************************** */

template <typename C = char>
std::basic_ostream<C>& operator<<(std::basic_ostream<C>& ost, util::StringList<C> const& strl)
{
    return ost << strl.to_string();
}

#endif /* __HH_UTIL_STRING_LIST */