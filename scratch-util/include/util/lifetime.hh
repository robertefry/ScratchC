
#ifndef HH_UTIL_LIFETIME
#define HH_UTIL_LIFETIME

#include "core.hh"

#include <iostream>

namespace util
{

    struct LifetimeTracker
    {
        LifetimeTracker()
        {
            std::cout << SC_GetFunctionName() << "\n";
        }
        explicit LifetimeTracker(int)
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
        LifetimeTracker& operator=(LifetimeTracker const&)
        {
            std::cout << SC_GetFunctionName() << "\n";
            return *this;
        }
        LifetimeTracker(LifetimeTracker&&) noexcept
        {
            std::cout << SC_GetFunctionName() << "\n";
        }
        LifetimeTracker& operator=(LifetimeTracker&&) noexcept
        {
            std::cout << SC_GetFunctionName() << "\n";
            return *this;
        }
    };

} // namespace util

#endif /* HH_UTIL_LIFETIME */
