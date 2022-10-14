
#include <cmath>
#include <bitset>
#include <vector>

class prime_sieve
{
    static constexpr size_t chunk_size = 32;

    struct chunk_t
    {
        std::bitset<chunk_size> bits;

        auto operator[](size_t bit) { return bits[bit]; }
        auto operator[](size_t bit) const { return bits[bit]; }
    };

    static constexpr size_t idx(size_t p) { return (p-3)/2; }
    static constexpr size_t chk(size_t p) { return idx(p) / chunk_size; }
    static constexpr size_t bit(size_t p) { return idx(p) % chunk_size; }

public:
    explicit prime_sieve(size_t n)
    {
        if (n <= 16)
        {
            m_PrimesFound = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
            m_HasRun = true;
            return;
        }

        size_t const sieve_size = 1 + [&]() -> size_t
            // numerically solve the prime counting function π(x) = n
        {
            size_t x_last = 0, x_curr = n;
            while (x_curr > x_last)
            {
                x_last = x_curr;
                x_curr = n * log(x_curr);
            }
            return x_last;
        }();
        m_Chunks = std::vector<chunk_t>(chk(sieve_size)+(bool)bit(sieve_size));

        m_PrimesFound.reserve(n);
    }

    void run()
    {
        if (m_HasRun) return;

        
    }

private:
    std::vector<chunk_t> m_Chunks{};

    bool m_HasRun = false;
    std::vector<size_t> m_PrimesFound{};
};
