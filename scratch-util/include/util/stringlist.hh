
#ifndef __HH_UTIL_STRING_LIST_
#define __HH_UTIL_STRING_LIST_

#include <list>
#include <string>

/* ************************************************************************** */
//  [Definition] util::basic_stringlist
/* ************************************************************************** */

namespace util
{

    template <typename C, typename T>
    struct basic_stringlist_formatter; // to be specialised

    template <typename T> using stringlist_formatter = basic_stringlist_formatter<char,T>;
    template <typename T> using wstringlist_formatter = basic_stringlist_formatter<wchar_t,T>;

    template <typename C>
    class basic_stringlist
    {
    public:
        explicit basic_stringlist() = default;
        virtual ~basic_stringlist() = default;

        operator std::basic_string<C>() const { return to_string(); }

    public:
        basic_stringlist<C>& operator<<(basic_stringlist<C> const&);
        basic_stringlist<C>& operator<<(basic_stringlist<C>&&);

        basic_stringlist<C>& operator<<(std::basic_string<C> const&);
        basic_stringlist<C>& operator<<(std::basic_string<C>&&);

        template <typename T> basic_stringlist<C>& operator<<(T const&);
        template <typename T> basic_stringlist<C>& operator<<(T&);
        template <typename T> basic_stringlist<C>& operator<<(T const&&);
        template <typename T> basic_stringlist<C>& operator<<(T&&);

        std::basic_string<C> to_string(std::basic_string<C> const& delim = "") const;

    private:
        std::list<std::basic_string<C>> m_List{};
    };

    using stringlist = basic_stringlist<char>;
    using wstringlist = basic_stringlist<wchar_t>;

} // namespace util

template <typename C>
std::basic_ostream<C>& operator<<(std::basic_ostream<C>& ost, util::basic_stringlist<C> const& strl)
{
    return ost << strl.to_string();
}

/* ************************************************************************** */
//  [Implementation] util::basic_stringlist::formatter
/* ************************************************************************** */

#include <sstream>

namespace util
{

    template <typename C, typename T>
        requires std::convertible_to<T,std::basic_string<C>>
    struct basic_stringlist_formatter<C,T>
    {
        void format(basic_stringlist<C>& strl, T const& obj)
        {
            strl << static_cast<std::basic_string<C>>(obj);
        }
    };

    template <typename C, typename T>
        requires std::is_arithmetic<T>::value
    struct basic_stringlist_formatter<C,T>
    {
        void format(basic_stringlist<C>& strl, T t)
        {
            strl << std::to_string(t);
        }
    };

    template <typename C, typename T>
    concept has_to_stringlist =
        requires (basic_stringlist<C>& strl, T const obj) { obj.to_stringlist(strl); } ||
        requires (basic_stringlist<C>& strl, T obj)       { obj.to_stringlist(strl); };

    template <typename C, typename T>
        requires has_to_stringlist<C,T>
    struct basic_stringlist_formatter<C,T>
    {
        void format(basic_stringlist<C>& strl, T const& obj)  { obj.to_stringlist(strl); }
        void format(basic_stringlist<C>& strl, T& obj)        { obj.to_stringlist(strl); }
        void format(basic_stringlist<C>& strl, T const&& obj) { obj.to_stringlist(strl); }
        void format(basic_stringlist<C>& strl, T&& obj)       { obj.to_stringlist(strl); }
    };

} // namespace util

/* ************************************************************************** */
//  [Implementation] util::basic_stringlist
/* ************************************************************************** */

namespace util
{

    template <typename C>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(basic_stringlist<C> const& strl)
    {
        m_List.insert(m_List.end(),strl.m_List.begin(),strl.m_List.end());
        return *this;
    }

    template <typename C>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(basic_stringlist<C>&& strl)
    {
        m_List.splice(m_List.end(),strl.m_List);
        return *this;
    }

    template <typename C>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(std::basic_string<C> const& str)
    {
        m_List.push_back(str);
        return *this;
    }

    template <typename C>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(std::basic_string<C>&& str)
    {
        m_List.push_back(std::move(str));
        return *this;
    }

    template <typename C> template <typename T>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(T const& obj)
    {
        basic_stringlist<C> strl;
        basic_stringlist_formatter<C,T>{}.format(strl,obj);
        return this->operator<<(std::move(strl));
    }

    template <typename C> template <typename T>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(T& obj)
    {
        basic_stringlist<C> strl;
        basic_stringlist_formatter<C,T>{}.format(strl,obj);
        return this->operator<<(std::move(strl));
    }

    template <typename C> template <typename T>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(T const&& obj)
    {
        basic_stringlist<C> strl;
        basic_stringlist_formatter<C,T>{}.format(strl,std::move(obj));
        return this->operator<<(std::move(strl));
    }

    template <typename C> template <typename T>
    basic_stringlist<C>& basic_stringlist<C>::operator<<(T&& obj)
    {
        basic_stringlist<C> strl;
        basic_stringlist_formatter<C,T>{}.format(strl,std::move(obj));
        return this->operator<<(std::move(strl));
    }

    template <typename C>
    std::basic_string<C> basic_stringlist<C>::to_string(std::basic_string<C> const& delim) const
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

#endif /* __HH_UTIL_STRING_LIST_ */