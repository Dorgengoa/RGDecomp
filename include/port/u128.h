/* 128-bit integers for the PC port (PLAN.md hazard "128-bit types and MMI").
 *
 * mwcc's `unsigned __int128` is the R5900 qword: sizeof 16, alignment 16,
 * moved with one lq/sq, zeroed with `sq $0`, cast to and from u64/s32, shifted
 * and OR-ed by a few packet builders, passed and returned by value.  i686
 * clang has no __int128, so ingest stage `int128` (tools/portxform.py)
 * rewrites the spelling to rg_u128 / rg_s128, defined here as clang's
 * _BitInt(128) with the alignment forced to 16 (plain _BitInt(128) is 8 on
 * i686).  _BitInt keeps every integer operation the game uses -- `= 0`,
 * casts, shifts, |, &, +, ==, and even * / % (lowered inline, no libcall) --
 * and the same little-endian byte layout as the EE, so a struct member or a
 * union pun over four f32 sees the same bytes.  tests/test_u128.c proves it.
 *
 * C++: _BitInt is a clang extension there (-Wbit-int-extension, silenced).
 */
#ifndef RG_PORT_U128_H
#define RG_PORT_U128_H

#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wbit-int-extension"
#endif
typedef unsigned _BitInt(128) __attribute__((aligned(16))) rg_u128;
typedef signed _BitInt(128) __attribute__((aligned(16))) rg_s128;
#if defined(__clang__)
#  pragma clang diagnostic pop
#endif

#ifdef __cplusplus
static_assert(sizeof(rg_u128) == 16 && alignof(rg_u128) == 16, "rg_u128 layout");
#else
_Static_assert(sizeof(rg_u128) == 16 && _Alignof(rg_u128) == 16, "rg_u128 layout");
_Static_assert(sizeof(rg_s128) == 16 && _Alignof(rg_s128) == 16, "rg_s128 layout");
#endif

#define RG_U128(hi, lo) (((rg_u128)(unsigned long long)(hi) << 64) | (rg_u128)(unsigned long long)(lo))
#define RG_U128_LO(v) ((unsigned long long)(v))
#define RG_U128_HI(v) ((unsigned long long)((rg_u128)(v) >> 64))

#endif /* RG_PORT_U128_H */
