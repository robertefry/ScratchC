
// #include "prime_sieve.hh"

#include <vector>

#include <hayai.hpp>

BENCHMARK(PRIME_SIEVE,NAIVE,10,10)
{
    auto const sieve = [](int n)
    {
        std::vector<bool> is_prime (n,false);

        for (int i = 2; i < n; ++i)
            if (is_prime[i])
                for (int j = i*i; j < n; j += i)
                    is_prime[j] = 0;

        return is_prime;
    };
    (void) sieve(1'000'000);
}
BENCHMARK(PRIME_SIEVE,NAIVE_OPTIMISED,10,10)
{
    auto const sieve = [](int n)
    {
        std::vector<bool> is_prime (n,false);

        int sqrt_n = [&]()
        {
            int x[2] = {0,n};
            while (x[0] < x[1]) { x[0] = x[1]; x[1] = n * x[0]; }
            return x[0];
        }();

        for (int i = 2; i < sqrt_n; ++i)
            if (is_prime[i])
                for (int j = i*i; j < n; j += i)
                    is_prime[j] = 0;

        return is_prime;
    };
    (void) sieve(1'000'000);
}
