/* rg_u128 / rg_s128 (include/port/u128.h): layout + every operation class
 * the game uses on u128 (census in docs/PORT-HEADERS.md).  Exit 0 = pass.
 * The type names are spelled exactly as the int128 ingest stage leaves a
 * game file: `typedef rg_u128 u128;`. */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include "port/u128.h"

typedef rg_u128 u128;
typedef rg_s128 s128;
typedef unsigned long long u64;
typedef float f32;

/* -- layout: identical to the EE (size 16, align 16, little-endian) */
_Static_assert(sizeof(u128) == 16, "size");
_Static_assert(_Alignof(u128) == 16, "align");
_Static_assert(_Alignof(s128) == 16, "align s");
typedef struct { f32 a; f32 b; unsigned char pad8[8]; u128 v10; u128 v20; } Out; /* AnimKeyBlendMaterial */
_Static_assert(offsetof(Out, v10) == 0x10 && offsetof(Out, v20) == 0x20 && sizeof(Out) == 0x30, "Out");
typedef struct { unsigned int x; u128 q; } Pad; /* member after a word: padded to 16 */
_Static_assert(offsetof(Pad, q) == 16 && sizeof(Pad) == 32, "Pad");
typedef struct { u128 q; unsigned int x; } Tail; /* tail padding to 16 */
_Static_assert(sizeof(Tail) == 32, "Tail");
typedef union { u128 q; f32 f[4]; unsigned int w[4]; } Pun;
_Static_assert(sizeof(Pun) == 16 && _Alignof(Pun) == 16, "Pun");
u128 g_arr[3];
_Static_assert(sizeof(g_arr) == 48, "array stride");

static int fails;
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); fails++; } } while (0)

/* by-value parameters and returns across a real call boundary */
__attribute__((noinline)) u128 pass_through(u128 a, int s, u128 b) { return (a << s) | (b >> 3); }
__attribute__((noinline)) s128 neg(s128 v) { return -v; }
__attribute__((noinline)) void store_zero(u128 *p) { *p = 0; } /* VEC4_ZERO */
__attribute__((noinline)) u128 copy_through(const u128 *p) { return *p; }

extern int test_u128_cpp(void);

int main(void)
{
    u128 a = RG_U128(0x0123456789ABCDEFull, 0xFEDCBA9876543210ull);
    unsigned char bytes[16];
    Pun pun;
    u128 z, r;
    s128 s;

    /* little-endian byte layout: low qword first, exactly like an EE sq */
    memcpy(bytes, &a, 16);
    CHECK(bytes[0] == 0x10 && bytes[7] == 0xFE && bytes[8] == 0xEF && bytes[15] == 0x01);

    /* casts to/from u64 / s32: truncation and zero/sign extension */
    CHECK((u64)a == 0xFEDCBA9876543210ull);
    CHECK((u64)(a >> 64) == 0x0123456789ABCDEFull);
    CHECK((u128)(u64)-1 >> 64 == 0);
    CHECK((u128)(int)-1 == ~(u128)0);           /* s32 -> u128 sign-extends */
    CHECK((unsigned int)a == 0x76543210u);

    /* shifts / OR / AND / XOR / NOT (GIF tag packing) */
    r = pass_through(a, 4, a);
    CHECK(RG_U128_HI(r) == ((0x0123456789ABCDEFull << 4) | (0xFEDCBA9876543210ull >> 60) | (0x0123456789ABCDEFull >> 3)));
    CHECK(RG_U128_LO(r) == ((0xFEDCBA9876543210ull << 4) | ((0xFEDCBA9876543210ull >> 3) | (0x0123456789ABCDEFull << 61))));
    CHECK(((a & ~(u128)0xFF) | 0x5A) == RG_U128(0x0123456789ABCDEFull, 0xFEDCBA987654325Aull));
    CHECK((a ^ a) == 0 && ~(u128)0 == RG_U128(~0ull, ~0ull));
    CHECK(((u128)1 << 127) >> 127 == 1);

    /* arithmetic incl. carries across the 64-bit halves */
    CHECK(RG_U128(0, ~0ull) + 1 == RG_U128(1, 0));
    CHECK(RG_U128(1, 0) - 1 == RG_U128(0, ~0ull));
    CHECK(RG_U128(0, 0x100000000ull) * 0x100000000ull == RG_U128(1, 0));
    CHECK(a / 0x10000 == (a >> 16));
    CHECK(a % 0x10000 == 0x3210);

    /* signed: arithmetic shift, negate, compare */
    s = (s128)RG_U128(0x8000000000000000ull, 0);
    CHECK((s >> 127) == -1);
    CHECK(neg(5) == -5 && neg(-5) == 5);
    CHECK((s128)-1 < 0 && (u128)(s128)-1 > 0);

    /* = 0 stores and qword copies through pointers (VEC4_ZERO, Vec4 operator=) */
    z = a;
    store_zero(&z);
    CHECK(z == 0);
    pun.f[0] = 1.0f; pun.f[1] = 2.0f; pun.f[2] = 3.0f; pun.f[3] = 4.0f;
    r = copy_through(&pun.q);
    CHECK(memcmp(&r, &pun, 16) == 0);
    CHECK(((uintptr_t)&g_arr[1] & 15) == 0);
    {
        u128 local;           /* stack object alignment */
        CHECK(((uintptr_t)&local & 15) == 0);
        local = a;
        CHECK(local == a);
    }

    CHECK(test_u128_cpp());

    printf("test_u128: %s (%d failures)\n", fails ? "FAIL" : "PASS", fails);
    return fails != 0;
}
