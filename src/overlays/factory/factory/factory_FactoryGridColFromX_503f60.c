#include "types.h"

/* factory.bin overlay, 0x00503F60 -- map a world X coordinate to a grid column:
 * out of range gives -1, otherwise the offset divided by the row pitch,
 * clamped to the last row.  92 bytes, 23 instructions, 4 branches, 0 calls.
 *
 * * One of FOUR mnemonic-IDENTICAL leaves (ratio 1.000) found by ranking the
 * OPEN population against ITSELF: `004F3F60`-style axis pairs.  `00503F00`, `00503F60`,
 * `00503FC0` and `00504020` differ only in the five field offsets, so each is
 * a `sed` of this file.
 *
 * * `cvt.w.s` + `mfc1` is `(s32)f`, nothing else, and the listing shows it as
 * a `.word` -- rabbitizer will not name it on the R5900.
 *
 * ** The two range tests are ONE `if` with a short-circuit `||`, and that is
 * the whole unit.  Written as two separate `if`s -- or as `else if` -- mwcc
 * gives each `return -1` its own `li`, 8 bad words at the RIGHT LENGTH; the
 * `||` lets it fold the first arm into `bc1tl` + `addiu $2, $0, -0x1` in the
 * delay slot and share one `-1` block for the second.  Sixteen relational-token
 * spellings of the two compares (`<`, `>`, `!(>=)`, `!(<=)` in every position)
 * are a measured NULL -- mwcc canonicalises the float compare, so this is NOT
 * the [[factory-relational-token-branch-form]] axis but the JOIN.
 *
 * ** The clamp is `if (i >= n) { i = n - 1; } return i;`, not
 * `if (i < n) return i; return n - 1;` -- the latter is one word long and puts
 * the compare in `$at` behind a `beqzl`; `>= n` lands it in a GPR behind
 * `bnez`, exactly as [[at-compare-class]] predicts.
 */

typedef struct Obj {
    u8  pad000[0x298];
    s16 f298;
    s16 f29A;
    f32 f29C;
    u8  pad2A0[0x4];
    s16 f2A4;
    s16 f2A6;
    f32 f2A8;
    u8  pad2AC[0xC];
    f32 f2B8;
    f32 f2BC;
    f32 f2C0;
    f32 f2C4;
} Obj;

s32 factory_FactoryGridColFromX_503f60(Obj *o, f32 v)
{
    f32 lo;
    s32 n;
    s32 i;

    lo = o->f2B8;
    if (v < lo || o->f2BC < v) {
        return -1;
    }
    n = o->f2A4;
    i = (s32)((v - lo) / o->f2A8);
    if (i >= n) {
        i = n - 1;
    }
    return i;
}
