
#include <vector>
#include <functional>
#include <cmath>
using std::size_t;

std::vector<size_t> nth_primes(size_t n)
{
    using namespace std;
    if (n <= 16) return {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

    size_t const sieve_bound = 1 + [&]() -> size_t
    {
        size_t x_last = 0, x_curr = n;
        while (x_curr > x_last)
        {
            x_last = x_curr;
            x_curr = n * log(x_curr);
        }
        return x_last;
    }();
    function const index = [](size_t i) { return (i-3)/2; };
    vector<bool> sieve = vector<bool>(1+index(sieve_bound),true);

    vector<size_t> prime_list; prime_list.reserve(n);
    prime_list.push_back(2);

    function const mark_prime = [&](size_t i)
    {
        for (size_t j = i*3; j < sieve_bound; j += i*2)
        {
            sieve[index(j)] = false;
        }
        prime_list.push_back(i);
    };
    for (size_t i = 3, j = 1; j < n; i += 2)
    {
        if (sieve[index(i)]) { mark_prime(i); j += 1; }
    }
    return prime_list;
}
