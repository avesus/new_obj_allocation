#ifndef _CPP_ATTRIBUTES_H_
#define _CPP_ATTRIBUTES_H_

#define _UNREACHABLE_ __builtin_unreachable()
#define IMPOSSIBLE_COND(cond)                                                \
    {                                                                          \
        if (cond) {                                                            \
            _UNREACHABLE_;                                                     \
        }                                                                      \
    }

#define BRANCH_LIKELY(cond)   __builtin_expect(cond, 1)
#define BRANCH_UNLIKELY(cond) __builtin_expect(cond, 0)

#define PREFETCH_STD(addr) __builtin_prefetch((const void * const)(addr))

// Note PREFETCHT2 == PREFETCHT1
// pg 280
// https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-optimization-manual.pdf
#define PREFETCH_L(addr, i)  _mm_prefetch((void * const)(addr), i);

#define PREFETCH_W(addr) _m_prefetchw((void * const)(addr))

#define PREFETCH_NTA(addr)                                                     \
    asm("PREFETCHTNTA %[mloc]\n\t" : : [ mloc ] "g"(addr) :);

#define PREFETCH_COND(PREFETCH_FUNC, cond, addr)                               \
    {                                                                          \
        if constexpr (cond) {                                                  \
            PREFETCH_FUNC((const void * const)(addr));                         \
        }                                                                      \
    }

#define CACHE_ALIGN ALIGN_ATTR(CACHE_LINE_SIZE)
#define ALIGN_ATTR(alignment) __attribute__((aligned(alignment)))
#define PTR_ALIGNED_TO(addr, alignment)                                        \
    __builtin_assume_aligned(addr, alignment)


#define ALWAYS_INLINE inline __attribute__((always_inline))
#define NEVER_INLINE  __attribute__((noinline))


#define HOT_ATTR   __attribute__((hot))
#define COLD_ATTR  __attribute__((cold))
#define PURE_ATTR  __attribute__((pure))
#define CONST_ATTR __attribute__((const))


#endif
