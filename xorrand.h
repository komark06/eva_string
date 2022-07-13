#if !defined(__XORRAND_H)
#define __XORRAND_H

#include <stdint.h>

uint64_t seeds[3];

typedef uint64_t ticks;

#if defined(__i386__)
static inline ticks getticks(void)
{
    ticks ret;
    __asm__ __volatile__("rdtsc" : "=A"(ret));
    return ret;
}
#elif defined(__x86_64__)
static inline ticks getticks(void)
{
    unsigned hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long) lo) | (((unsigned long long) hi) << 32);
}
#elif defined(__aarch64__)
static inline ticks getticks(void)
{
    uint64_t val;
    __asm__ __volatile__("mrs %0, cntvct_el0" : "=r"(val));
    return val;
}
#else
#error "Unsupported platform"
#endif

static inline void seed_rand(uint64_t *_seeds)
{
    _seeds[0] = getticks() % 123456789;
    _seeds[1] = getticks() % 362436069;
    _seeds[2] = getticks() % 521288629;
}

static inline uint64_t xorshf96(uint64_t *x, uint64_t *y, uint64_t *z)
{
    *x ^= (*x) << 28;
    *x ^= (*x) >> 11;
    *x ^= (*x) << 53;
    uint64_t t = *x;
    *x = *y;
    *y = *z;
    *z = t ^ (*x) ^ (*y);
    return *z;
}

static inline uint64_t RAND(void)
{
    return xorshf96(seeds, seeds + 1, seeds + 2);
}

#endif  //! defined(__XORRAND_H)