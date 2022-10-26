
#ifndef __HH_UTIL_STRING_LIST_FORMAT_
#define __HH_UTIL_STRING_LIST_FORMAT_

#include "util/core.hh"

namespace util { template <typename C> class basic_stringlist; }

namespace util::format
{

    template <typename C, typename T>
    struct basic_stringlist_undefined_formatter
    {
        void format(basic_stringlist<C>& strl, T const&)
        {
            strl << "no formatter undefined for " << util::demangle<T>();
        }
    };
    template <typename T>
    using undefined_stringlist_formatter = basic_stringlist_undefined_formatter<char,T>;

    template <typename C, typename T>
    struct basic_stringlist_std_ostream_formatter
    {
        void format(basic_stringlist<C>& strl, T const& t)
        {
            std::basic_ostringstream<C> buffer;
            buffer << t;
            strl << buffer.str();
        }
    };
    template <typename T>
    using stringlist_std_ostream_formatter = basic_stringlist_std_ostream_formatter<char,T>;

    template <typename C, typename T>
    struct basic_stringlist_iterable_formatter
    {
        void format(basic_stringlist<C>& strl, T const& obj)
        {
            strl << "[";

            auto itr = obj.begin(), end = obj.end();
            if (itr != end)
            {
                strl << *itr;

                for (++itr; itr != end; ++itr)
                {
                    strl << "," << *itr;
                }
            }
            strl << "]";
        }
    };
    template <typename T>
    using stringlist_iterable_formatter = basic_stringlist_iterable_formatter<char,T>;

    template <typename C, typename T>
    struct basic_stringlist_adapter_iterable_formatter
        : private basic_stringlist_iterable_formatter<C,typename adapters<T>::container_type>
    {
        void format(basic_stringlist<C>& strl, T const& obj)
        {
            using formatter = basic_stringlist_iterable_formatter<C,typename adapters<T>::container_type>;
            formatter::format(strl,adapters<T>::get(obj));
        }
    };
    template <typename T>
    using stringlist_adapter_iterable_formatter = basic_stringlist_adapter_iterable_formatter<char,T>;

} // namespace util::format

#endif /* __HH_UTIL_STRING_LIST_FORMAT_ */
