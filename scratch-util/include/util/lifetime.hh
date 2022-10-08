
#ifndef __HH_UTIL_LIFETIME_
#define __HH_UTIL_LIFETIME_

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

} // namespace util

#endif /* __HH_UTIL_LIFETIME_ */
