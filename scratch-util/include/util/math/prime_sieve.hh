
#ifndef __HH_UTIL_MATH_PRIME_SIEVE_
#define __HH_UTIL_MATH_PRIME_SIEVE_

#include "util/math/integer.hh"

#include <functional>
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

namespace util::math
{

    class prime_sieve
    {
        struct chunk_t : std::atomic<uint8_t>
        {
            using base_t = uint8_t;
            chunk_t() { *this |= static_cast<base_t>(-1); }
        };

    public:
        explicit prime_sieve(size_t size)
        {
            size_t const num_chunks = chk(size-1) + (bool)bit(size-1);
            m_Chunks = std::make_unique<chunk_t[]>(num_chunks);
            m_Size = num_chunks * sizeof(chunk_t) * CHAR_BIT * 2 + 3;
        }

        static size_t idx(size_t i) { return (i-3) / 2; }
        static size_t chk(size_t i) { return idx(i) / (sizeof(chunk_t) * CHAR_BIT); }
        static size_t bit(size_t i) { return idx(i) % (sizeof(chunk_t) * CHAR_BIT); }

        auto operator[](size_t i) const { return m_Chunks.get()[chk(i)] & (chunk_t::base_t{0x1} << bit(i)); }

        inline void run(size_t num_workers);
        inline auto get_sieve() const -> std::vector<bool>;

        inline bool is_prime(size_t x) const;
        inline auto primes() const -> std::vector<size_t>;

    protected:
        void mark(size_t i) { m_Chunks.get()[chk(i)] &= ~(chunk_t::base_t{0x1} << bit(i)); }

    private:
        std::unique_ptr<chunk_t[]> m_Chunks{};
        size_t m_Size{};
    };

    void prime_sieve::run(size_t num_workers = std::thread::hardware_concurrency())
    {
        class worker_pool
        {
        public:
            ~worker_pool()
            {
                m_ShouldTerminate = true;
                m_JobQueue.notify_all();
                for (auto& worker : m_Workers) if (worker.joinable()) worker.join();

                while (not m_JobQueue.empty())
                {
                    auto job = std::move(m_JobQueue.front()); m_JobQueue.pop();
                    job();
                }
            }
            explicit worker_pool(size_t num_workers)
            {
                m_Workers.reserve(num_workers);
                for (size_t i = 0; i < num_workers; ++i) m_Workers.emplace_back([this](){ this->run(); });
            }
            void enqueue(std::function<void(void)>&& job)
            {
                {
                    std::unique_lock lock {m_JobQueue.mtx};
                    m_JobQueue.push(std::move(job));
                }
                m_JobQueue.notify_one();
            }
        private:
            void run()
            {
                while (not m_ShouldTerminate)
                {
                    std::function<void(void)> job;
                    {
                        std::unique_lock lock {m_JobQueue.mtx};
                        if (m_JobQueue.empty()) m_JobQueue.wait(lock);

                        if (m_ShouldTerminate) return;
                        if (m_JobQueue.empty()) continue;
                        job = std::move(m_JobQueue.front()); m_JobQueue.pop();
                    }
                    job();
                }
            }
        private:
            std::vector<std::thread> m_Workers{};
            bool m_ShouldTerminate = false;

            struct job_queue_t : std::queue<std::function<void(void)>>, std::condition_variable {
                std::mutex mtx;
            } m_JobQueue{};
        };
        worker_pool workers {num_workers};

        for (size_t i = 3, k = isqrt(m_Size); i <= k; i += 2)
        {
            if ((*this)[i]) workers.enqueue([this,i]{ for (size_t j = i*3; j < m_Size; j += 2*i) mark(j); });
        }
    }

    auto prime_sieve::get_sieve() const -> std::vector<bool>
    {
        std::vector<bool> sieve; sieve.resize(m_Size);
        {
            sieve[2] = true;
            for (size_t i = 3; i < m_Size; i += 2) sieve[i] = (*this)[i];
        }
        return sieve;
    }

    bool prime_sieve::is_prime(size_t x) const
    {
        if (x == 0 || x == 1) return false;
        if (x == 2) return true;
        return (*this)[x];
    }

    auto prime_sieve::primes() const -> std::vector<size_t>
    {
        size_t const num_primes = [x=m_Size]() -> size_t // prime-counting function upper-bound
        {
            size_t est = (x == 0) ? 0 : 2 * x / log2i(x);
            return est - (est >> 4) - (est >> 5);
        }();

        std::vector<size_t> primes; primes.reserve(num_primes);
        {
            primes.push_back(2);

            for (size_t i = 3; i < m_Size; i += 2)
            {
                if ((*this)[i]) primes.push_back(i);
            }
        }
        return primes;
    }

    inline std::vector<size_t> nth_primes(size_t n)
    {
        if (n <= 16) return {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

        // numerically solve an upper-bound to the prime counting function
        size_t const sieve_size = [&]() -> size_t
        {
            size_t x_last = 0, x_curr = n * util::math::log2i(n);
            while (x_curr > x_last)
            {
                x_last = x_curr;
                x_curr = n * util::math::log2i(x_curr);
            }
            return (x_curr/3)<<1;
        }();

        util::math::prime_sieve sieve {sieve_size};
        sieve.run(std::thread::hardware_concurrency());
        return sieve.primes();
    }

} // namespace util::math

#endif /* __HH_UTIL_MATH_PRIME_SIEVE_ */
