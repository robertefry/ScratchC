
#ifndef __HH_UTIL_
#define __HH_UTIL_

#ifdef __GNUC__
#define SC_GetFunctionName() __PRETTY_FUNCTION__
#else
#define SC_GetFunctionName() "<funcname>"
#endif

#include <iterator>
#include <memory>

#include <cxxabi.h>
#include <type_traits>

namespace util
{

    template <typename T>
    std::string demangle() noexcept
    {
        using given_t = T; using value_t = std::remove_reference_t<given_t>;

        struct free_deleter { void operator()(void* ptr) { free(ptr); }};
        std::unique_ptr<char,free_deleter> demangled {
            __cxxabiv1::__cxa_demangle(typeid(value_t).name(),nullptr,nullptr,nullptr) };
        std::string result = demangled.get();

        if constexpr (std::is_const_v<value_t>) {
            result += " const";
        }
        if constexpr (std::is_volatile_v<value_t>) {
            result += " volatile";
        }
        if constexpr (std::is_lvalue_reference_v<given_t>) {
            result += "&";
        }
        if constexpr (std::is_rvalue_reference_v<given_t>) {
            result += "&&";
        }
        return result;
    }
    template <typename T>
    std::string demangle(T const&) noexcept
    {
        return demangle<T>();
    }

    template <typename t_adapter>
    struct adapters : t_adapter
    {
        using container_type = typename t_adapter::container_type;

        static typename t_adapter::container_type const& get(t_adapter const& adapter) {
            return adapter.*&adapters::c;
        }
        static typename t_adapter::container_type& get(t_adapter& adapter) {
            return adapter.*&adapters::c;
        }
        adapters() = delete;
    };

    template <typename T, typename = void>
    struct is_std_hashable : std::false_type {};

    template <typename T>
    struct is_std_hashable<T,
        std::void_t<decltype(std::declval<std::hash<T>>()(std::declval<T>()))>>
    : std::true_type {};

    template <typename T>
    constexpr bool is_std_hashable_v = is_std_hashable<T>::value;

    template <typename T, typename = void>
    struct is_std_iterable : std::false_type {};

    template <typename T>
    struct is_std_iterable<T,std::void_t<
        decltype(std::begin(std::declval<T>())),decltype(std::end(std::declval<T>())) >>
    : std::true_type {};

    template <typename T>
    constexpr bool is_std_iterable_v = is_std_iterable<T>::value;

    template <typename Iterable>
    struct std_iterable {
        using iterator_t = decltype(std::begin(std::declval<Iterable>()));
        using element_t = typename std::iterator_traits<iterator_t>::value_type;
    };

    template <typename Iterable>
    using std_iterable_iterator_t = typename std_iterable<Iterable>::iterator_t;

    template <typename Iterable>
    using std_iterable_element_t = typename std_iterable<Iterable>::element_t;

    template <typename T, typename = void>
    struct has_std_size : std::false_type {};

    template <typename T>
    struct has_std_size<T,std::void_t<decltype(std::size(std::declval<T>()))>> : std::true_type {};

    template <typename T>
    constexpr bool has_std_size_v = has_std_size<T>::value;
} // namespace util

#endif /* __HH_UTIL_ */
