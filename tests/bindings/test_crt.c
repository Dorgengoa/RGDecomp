/* SPDX-License-Identifier: CC0-1.0 */
/* src/crt semantics: hand-computed values for the places where the game's
 * runtime differs from a host CRT (newlib rand, BSD qsort order, ctype
 * quirks, soft-double conversion rounding/saturation, MSL array cookies,
 * the global destructor chain, the sbrk heap). */
#include "bt.h"
#include "crt.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <xmmintrin.h>

extern size_t bt_sbrk_limit;

/* ---- qsort reference: insertion-sorted copy + the order check ---- */
typedef struct {
    int key, id;
} kv;
static int cmp_kv(const void *a, const void *b)
{
    return ((const kv *)a)->key - ((const kv *)b)->key;
}
static int ncmp;
static int cmp_int(const void *a, const void *b)
{
    ncmp++;
    return *(const int *)a - *(const int *)b;
}

static int ctor_log[8], nlog;
static void ctor_cb(void *obj, int flag)
{
    *(int *)obj = 100 + nlog;
    ctor_log[nlog++] = flag;
}
static void dtor_cb(void *obj, int flag)
{
    ctor_log[nlog++] = *(int *)obj * flag;
}

int bt_crt(void)
{
    int f = 0;
    char buf[64];

    /* ---- rand: newlib LCG, state starts at 1 ---- */
    BT_EQ(f, Rand_133710(), BT_WRONG(1481765933));
    BT_EQ(f, Rand_133710(), 1085377743);
    BT_EQ(f, Rand_133710(), 1270216262);
    Srand_1336f8(12345);
    BT_EQ(f, Rand_133710(), 134732914);

    /* ---- ctype quirks ---- */
    BT_EQ(f, Toupper_1363e0('a'), 'A');
    BT_EQ(f, Toupper_1363e0('A'), 'A');
    BT_EQ(f, Toupper_1363e0(-1), -1);
    BT_EQ(f, Toupper_1363e0(-127), -159); /* retail table: byte before _ctype_ has _L */
    BT_EQ(f, Toupper_1363e0(0xE9), 0xE9);
    strcpy(buf, "abZ9\x81q");
    Strupr_136390(buf);
    BT_EQ(f, strcmp(buf, "ABZ9\x61Q"), 0); /* 0x81 = -127 -> -159 = 0x61 */
    BT_EQ(f, Strcasecmp_1345b8("Hello", "hELLo"), 0);
    BT_EQ(f, Strcasecmp_1345b8("abc", "ABD"), -1);
    BT_EQ(f, Strcasecmp_1345b8("ab", "abc"), -'c');
    BT_EQ(f, Strcasecmp_1345b8("\xE9", "\xC9"), 32); /* loop folds signed, end unsigned */
    BT_EQ(f, Strncasecmp_134ce8("abcX", "ABCy", 3), 0);
    BT_EQ(f, Strncasecmp_134ce8("abcX", "ABCy", 4), 'x' - 'y');
    BT_EQ(f, Strncasecmp_134ce8("a", "b", 0), 0);
    BT_EQ(f, Strncasecmp_134ce8("ab", "AB", 10), 0);

    /* ---- printf family ---- */
    Sprintf_1343b8(buf, "%d:%s:%.2f:%04x", -12, "ok", 2.345, 0xAB);
    BT_EQ(f, strcmp(buf, "-12:ok:2.35:00ab") == 0 || strcmp(buf, "-12:ok:2.34:00ab") == 0, 1);
    BT_EQ(f, Index_1308f0("hello", 'l') - (char *)0 != 0, 1);
    BT_EQ(f, Strstr_135138("abcabd", "abd") != NULL, 1);
    BT_EQ(f, Strtol_136360("0x1F", NULL, 0), 31);
    BT_FBITS(f, (float)Atof_12dee8("1.5"), 1.5f);

    /* ---- qsort: newlib's order of equal keys ---- */
    {
        /* 12 elements, keys with duplicates; the expected ids come from an
         * independent Python model of the 4.4BSD qsort (n > 7: median of 3,
         * 3-way partition, vecswap); a host qsort orders equal keys
         * differently */
        kv v[12] = {{3, 0}, {1, 1}, {2, 2}, {1, 3}, {3, 4}, {2, 5},
                    {1, 6}, {3, 7}, {2, 8}, {1, 9}, {2, 10}, {3, 11}};
        int i, sorted = 1;
        Qsort_132d08(v, 12, sizeof v[0], cmp_kv);
        for (i = 1; i < 12; i++)
            sorted &= v[i - 1].key <= v[i].key;
        BT_EQ(f, sorted, 1);
        {
            static const int want[12] = {1, 9, 6, 3, 2, 10, 5, 8, 11, 4, 7, 0};
            for (i = 0; i < 12; i++)
                BT_EQ(f, v[i].id, want[i]);
        }
        /* 100 ints, descending with repeats: sorted, and n log n compares */
        {
            int w[100];
            for (i = 0; i < 100; i++)
                w[i] = (100 - i) / 3;
            ncmp = 0;
            Qsort_132d08(w, 100, sizeof w[0], cmp_int);
            sorted = 1;
            for (i = 1; i < 100; i++)
                sorted &= w[i - 1] <= w[i];
            BT_EQ(f, sorted, 1);
            BT_EQ(f, ncmp < 1000, 1);
        }
    }

    /* ---- conversions ---- */
    BT_EQ(f, DoubleToUInt_13bb78(3.9), 3);
    BT_EQ(f, DoubleToUInt_13bb78(-1.5), 0);         /* negative -> 0 */
    BT_EQ(f, DoubleToUInt_13bb78(1e10), 0xFFFFFFFFu); /* saturates */
    BT_EQ(f, DoubleToUInt_13bb78(NAN), 0);
    BT_EQ(f, dptoli(3e10), 0x7FFFFFFF);
    BT_EQ(f, dptoli(-3e10), (int)0x80000000u);
    BT_EQ(f, dptoli(-2.9), -2);
    BT_EQ(f, (long long)DoubleToU64_13ab28(1e19), 10000000000000000000ull);
    BT_EQ(f, DoubleToU64_13ab28(-5.0), 0);
    BT_EQ(f, DoubleToS64_13ac40(-3.7), -3);
    BT_EQ(f, DoubleToS64_13ac40(4503599627370497.0), 4503599627370497ll);
    BT_EQ(f, FloatToS64_13ade0(-16777216.0f), -16777216ll);
    BT_EQ(f, (long long)FloatToU64_13acb8(1.8446743e19f), (long long)0xFFFFFF0000000000ull);
    {
        double d = U64ToDouble_100370(0xFFFFFFFFFFFFFFFFull);
        BT_EQ(f, d == 18446744073709551616.0, 1);
        d = U64ToDouble_100370(0x8000000000000401ull); /* sticky halving rounds up */
        BT_EQ(f, d == 9223372036854777856.0, 1);
        BT_EQ(f, UIntToDouble_100320(0xFFFFFFFFu) == 4294967295.0, 1);
        BT_EQ(f, S64ToDouble_13a998(-1) == -1.0, 1);
        BT_EQ(f, S64ToDouble_13a998(-4294967296ll - 5) == -4294967301.0, 1);
    }
    {
        /* 2^60 + 2^36 + 1: via double it would tie to even (2^60); the
         * sticky bit gives the correctly rounded 2^60 + 2^37 */
        float x = S64ToFloat_13aa40(0x1000001000000001ll);
        unsigned bits;
        memcpy(&bits, &x, 4);
        BT_EQ(f, bits, 0x5D800001u);
        BT_FBITS(f, S64ToFloat_13aa40(-3), -3.0f);
    }
    BT_EQ(f, DoubleCmp_13b948(1.0, 2.0), -1);
    BT_EQ(f, DoubleCmp_13b948(2.0, 2.0), 0);
    BT_EQ(f, DoubleCmp_13b948(NAN, 0.0), 1);
    BT_EQ(f, DoubleCmp_13b948(0.0, NAN), 1);
    BT_EQ(f, Divdi3_139188(-7, 2), -3);
    BT_EQ(f, ModDi3_139820(-7, 2), -1);
    BT_EQ(f, Divdi3_139188((long long)0x8000000000000000ull, -1), (long long)0x8000000000000000ull);
    BT_EQ(f, Divdi3_139188(5, 0), 0); /* no trap */
    BT_EQ(f, (long long)UDivDi3_139eb0(0xFFFFFFFFFFFFFFFFull, 3), 0x5555555555555555ll);
    BT_EQ(f, (long long)UModDi3_13a430(10, 0), 10);
    BT_EQ(f, Finite_1283d8(INFINITY), 0);
    BT_EQ(f, Isnan_128658(NAN), 1);
    BT_EQ(f, Isnan_128658(INFINITY), 0);
    BT_FBITS(f, dptofp(dpmul(fptodp(1.5f), litodp(3))), 4.5f);

    /* ---- MSL arrays: cookie {size, n, dtor}, ctor(this, 1), dtor(this, -1) backwards ---- */
    {
        unsigned char block[16 + 3 * 8] __attribute__((aligned(16)));
        unsigned *cookie = (unsigned *)block;
        int *arr;
        nlog = 0;
        arr = (int *)ConstructNewArray_100710(block, ctor_cb, dtor_cb, 8, 3);
        BT_EQ(f, (unsigned char *)arr - block, 16);
        BT_EQ(f, cookie[0], 8);
        BT_EQ(f, cookie[1], 3);
        BT_EQ(f, cookie[2] == (unsigned)(size_t)dtor_cb, 1);
        BT_EQ(f, arr[0], 100);
        BT_EQ(f, arr[4], 102);
        BT_EQ(f, ctor_log[2], 1);
        DestroyArray_1005b0(arr, dtor_cb, 8, 3);
        BT_EQ(f, ctor_log[3], -102); /* last element first */
        BT_EQ(f, ctor_log[5], -100);
        BT_EQ(f, ConstructNewArray_100710(NULL, ctor_cb, dtor_cb, 8, 3) == NULL, 1);
    }

    /* ---- global destructor chain: LIFO, node popped before the call ---- */
    {
        extern struct { void *head; int pad[3]; } D_004853D0;
        struct node { struct node *next; rg_xtor_fn dtor; void *obj; } n1, n2;
        int o1 = 1, o2 = 2;
        n1.next = NULL, n1.dtor = dtor_cb, n1.obj = &o1;
        n2.next = &n1, n2.dtor = dtor_cb, n2.obj = &o2;
        D_004853D0.head = &n2;
        nlog = 0;
        DestroyGlobalChain_100d60(NULL);
        BT_EQ(f, nlog, 2);
        BT_EQ(f, ctor_log[0], -2);
        BT_EQ(f, ctor_log[1], -1);
        BT_EQ(f, D_004853D0.head == NULL, 1);
    }

    /* ---- MSL basic_string: short/long layout, retail capacity policy ---- */
    {
        struct { unsigned w0, size; char *data; } s = {0, 0, 0};
        StringReserve_107e80(&s, 5); /* still fits the short buffer: no-op */
        BT_EQ(f, s.w0, 0);
        StringReplace_106f90(&s, 0, 0, "hello", &"hello"[5], 0);
        BT_EQ(f, s.w0 & 0xFF, 10); /* short, size 5 */
        BT_EQ(f, memcmp((char *)&s + 1, "hello", 6), 0);
        StringReplace_106f90(&s, 5, 0, " world!!!!", &" world!!!!"[10], 0);
        BT_EQ(f, s.w0, (16u << 1) | 1); /* grew: (11 + 15) & ~15 = 16 */
        BT_EQ(f, s.size, 15);
        BT_EQ(f, strcmp(s.data, "hello world!!!!"), 0);
        StringReplace_106f90(&s, 1, 4, "EY", &"EY"[2], 0); /* in place, shrinks */
        BT_EQ(f, strcmp(s.data, "hEY world!!!!"), 0);
        BT_EQ(f, s.size, 13);
        StringReplaceFill_1075d0(&s, 0, 0, 3, '*');
        BT_EQ(f, s.w0, (32u << 1) | 1); /* 16 -> 32 (16 + 15 &~15 = 16, doubled) */
        BT_EQ(f, strcmp(s.data, "***hEY world!!!!"), 0);
        StringReserve_107e80(&s, 2); /* max(2, 16) + 16 & ~15 = 32 = cap: no-op */
        BT_EQ(f, s.w0, (32u << 1) | 1);
        StringReserve_107e80(&s, 40);
        BT_EQ(f, s.w0, (48u << 1) | 1);
        BT_EQ(f, strcmp(s.data, "***hEY world!!!!"), 0);
        /* self-referencing replace: insert a copy of the string's own tail */
        StringReplace_106f90(&s, 0, 0, s.data + 13, s.data + 16, 0);
        BT_EQ(f, strcmp(s.data, "!!!***hEY world!!!!"), 0);
        OperatorDelete_100840(s.data);
        {
            struct { unsigned w0, size; char *data; } t = {0, 0, 0};
            StringReserve_107e80(&t, 20); /* (20 + 16) & ~15 = 32 */
            BT_EQ(f, t.w0, (32u << 1) | 1);
            BT_EQ(f, t.size, 0);
            OperatorDelete_100840(t.data);
        }
    }

    /* ---- heap over sbrk ---- */
    {
        void *p[64];
        size_t free0;
        int i;
        p[0] = Malloc_130dd8(100);
        BT_EQ(f, p[0] != NULL, 1);
        BT_EQ(f, ((size_t)p[0] & 15), 0);
        /* two rounds: the first grows the heap (newlib extends top by whole
         * pages), the second must come back to the same free total */
        free0 = 0;
        for (int round = 0; round < 2; round++) {
            for (i = 1; i < 64; i++) {
                p[i] = Malloc_130dd8((size_t)(i * 37) % 900);
                memset(p[i], i, (size_t)(i * 37) % 900);
            }
            for (i = 1; i < 64; i += 2)
                Free_130e30(p[i]);
            BT_EQ(f, rg_crt_heap_check(), 0);
            for (i = 2; i < 64; i += 2) {
                BT_EQ(f, ((unsigned char *)p[i])[0] == (unsigned char)i || (i * 37) % 900 == 0, 1);
                Free_130e30(p[i]);
            }
            BT_EQ(f, rg_crt_heap_check(), 0);
            if (round == 0)
                free0 = rg_crt_heap_free_bytes();
        }
        BT_EQ(f, rg_crt_heap_free_bytes() == free0, 1); /* everything coalesced back */
        {
            void *a = Memalign_130ba8(256, 1000);
            BT_EQ(f, ((size_t)a & 255), 0);
            BT_EQ(f, rg_crt_heap_check(), 0);
            Free_130e30(a);
        }
        BT_EQ(f, rg_crt_heap_free_bytes() == free0, 1);
        {
            /* the heap ends where sbrk says: a too-big request is NULL */
            void *big;
            bt_sbrk_limit = 4u << 20;
            BT_EQ(f, Malloc_130dd8(5u << 20) == NULL, 1);
            big = Malloc_130dd8(3u << 20);
            BT_EQ(f, big != NULL, 1);
            Free_130e30(big);
            BT_EQ(f, rg_crt_heap_check(), 0);
        }
        Free_130e30(p[0]);
        BT_EQ(f, OperatorNew_100990(0) != NULL, 1);
    }
    {
        /* float libm (src/crt/crt_eelibm.c, 2026-10-24): under the game's EE MXCSR (round
         * toward zero + FTZ + DAZ) the retail fdlibm float routines, within 1 ulp of retail
         * (references: PCSX2 probes and the retail code, tools/parity/eelibm_check.py; the
         * exact model build matches them bit for bit); under round to nearest the host libm. */
        static const struct { const char *fn; unsigned a, b, r; } ref[] = {
            {"tanf", 0x3f56ad22U, 0x00000000U, 0x3f8e64b5U},
            {"tanf", 0x3f5cfdceU, 0x00000000U, 0x3f95a8d1U},
            {"tanf", 0x4894bd8aU, 0x00000000U, 0xbfee1e2bU},
            {"asinf", 0x3ec17a26U, 0x00000000U, 0x3ec667d3U},
            {"asinf", 0x3f7b427fU, 0x00000000U, 0x3fb06434U},
            {"asinf", 0x3ef04970U, 0x00000000U, 0x3efa1decU},
            {"acosf", 0xbe97dab0U, 0x00000000U, 0x3fef9af7U},
            {"acosf", 0x3f798ec1U, 0x00000000U, 0x3e6636ebU},
            {"acosf", 0xbf661caaU, 0x00000000U, 0x402c080dU},
            {"powf", 0x3f7ff8efU, 0xcc22daebU, 0x7f7fffffU},
            {"powf", 0xbeeeb3f9U, 0x3f800000U, 0xbeeeb3f9U},
            {"powf", 0x3fddece8U, 0xc0400000U, 0x3e4479c5U},
            {"sinf", 0x4c4b103cU, 0x00000000U, 0x3d9ed623U},
            {"sinf", 0xd2d4f271U, 0x00000000U, 0xbf7f2eb6U},
            {"sinf", 0x5a06a8e9U, 0x00000000U, 0x3f6cd678U},
            {"sinf", 0x4b2af55dU, 0x00000000U, 0x3f684d5eU},
            {"cosf", 0x4cabb1a9U, 0x00000000U, 0x3e82fec9U},
            {"cosf", 0xccb3d1c0U, 0x00000000U, 0xbefaf73fU},
            {"cosf", 0xcbb15ec5U, 0x00000000U, 0xbf748c46U},
            {"atan2f", 0xc1a020a0U, 0x419fde00U, 0xbf494527U},
            {"atan2f", 0x3edc7a48U, 0xbf670c6aU, 0x402c9206U},
            {"atan2f", 0xbf581a4eU, 0x3f079710U, 0xbf815664U},
        };
        unsigned csr = _mm_getcsr();
        float x, y, r;
        unsigned rb;
        _mm_setcsr(0x1F80u | 0x6000u | 0x8040u);
        for (size_t i = 0; i < sizeof ref / sizeof ref[0]; i++) {
            memcpy(&x, &ref[i].a, 4);
            memcpy(&y, &ref[i].b, 4);
            switch (ref[i].fn[0] == 'a' ? ref[i].fn[1] * 2 + ref[i].fn[2] : ref[i].fn[0]) {
            case 't': r = Tanf_1290b8(x); break;
            case 'p': r = Powf_1291c0(x, y); break;
            case 'c': r = Cosf_128d30(x); break;
            case 's': r = Sinf_128fd0(x); break;
            case 's' * 2 + 'i': r = Asinf_129190(x); break;
            case 'c' * 2 + 'o': r = Acosf_129178(x); break;
            default: r = Atan2f_1291a8(x, y); break;
            }
            memcpy(&rb, &r, 4);
            BT_EQ(f, (rb > ref[i].r ? rb - ref[i].r : ref[i].r - rb) <= 1, 1);
        }
        /* EE division by zero: (x-x)/(x-x) = +FLT_MAX, not NaN */
        BT_FBITS(f, Asinf_129190(1.5f), 3.40282347e38f);
        BT_FBITS(f, Powf_1291c0(0.0f, -1.0f), 3.40282347e38f);
        _mm_setcsr(csr & ~0x6000u);
        BT_FBITS(f, Sinf_128fd0(0.5f), sinf(0.5f));
        BT_FBITS(f, Powf_1291c0(2.0f, 0.5f), powf(2.0f, 0.5f));
        _mm_setcsr(csr);
    }
    return f;
}
