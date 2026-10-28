/* SPDX-License-Identifier: CC0-1.0 */
/* Tiny check harness shared by the bindings tests (ctest -L bindings).
 * Each test file exports `int bt_<name>(void)` returning its failure count;
 * bindings_main.c runs them all.  RG_BT_WRONG flips one expected value per
 * suite (the deliberate-fault control: that build must FAIL). */
#ifndef RG_BT_H
#define RG_BT_H

#ifdef __cplusplus
extern "C" {
#endif
int printf(const char *, ...);
#ifdef __cplusplus
}
#endif

extern int bt_checks;

#define BT_FAIL(fails, ...)                                            \
    do {                                                               \
        printf("FAIL %s:%d: ", __FILE__, __LINE__);                    \
        printf(__VA_ARGS__);                                           \
        printf("\n");                                                  \
        (fails)++;                                                     \
    } while (0)

/* integer / bit-exact equality */
#define BT_EQ(fails, got, want)                                        \
    do {                                                               \
        long long g_ = (long long)(got), w_ = (long long)(want);       \
        bt_checks++;                                                   \
        if (g_ != w_)                                                  \
            BT_FAIL(fails, "%s = %lld (0x%llx), want %lld (0x%llx)",   \
                    #got, g_, g_, w_, w_);                             \
    } while (0)

/* float equality on the bit pattern (VU results are deterministic) */
#define BT_FBITS(fails, got, want)                                     \
    do {                                                               \
        float g_ = (got), w_ = (want);                                 \
        unsigned gb_, wb_;                                             \
        __builtin_memcpy(&gb_, &g_, 4);                                \
        __builtin_memcpy(&wb_, &w_, 4);                                \
        bt_checks++;                                                   \
        if (gb_ != wb_)                                                \
            BT_FAIL(fails, "%s = %.9g (0x%08x), want %.9g (0x%08x)",   \
                    #got, (double)g_, gb_, (double)w_, wb_);           \
    } while (0)

/* float within an absolute tolerance */
#define BT_NEAR(fails, got, want, tol)                                 \
    do {                                                               \
        double g_ = (got), w_ = (want);                                \
        bt_checks++;                                                   \
        if (!(g_ - w_ <= (tol) && w_ - g_ <= (tol)))                   \
            BT_FAIL(fails, "%s = %.9g, want %.9g (tol %g)", #got, g_,  \
                    w_, (double)(tol));                                \
    } while (0)

#ifdef RG_BT_WRONG
#define BT_WRONG(v) ((v) + 1)
#else
#define BT_WRONG(v) (v)
#endif

#endif
