#pragma optimization_level 3
/* === SESSION 54 (2026-09-12, SOLO): 53 BAD -> BYTE-IDENTICAL, 124 words.
 * MERGED into config/ocunits/normal.txt; NORMAL.BIN relinked BYTE-IDENTICAL
 * (610 units, 250,240 B) and ARMED (`b->f04 + 2` -> `+ 3` gives `1 differing
 * bytes, first at 0x5100 ... vram 0x004EEF80`, reverted clean).
 * FOUR EDITS, found by reading the MERGED TWIN normal_SpaceMenuOpenAnimStart_512e20
 * (clone2.py: 120w, opcode overlap 0.72, CALL OVERLAP 0.50) and then chasing
 * the length:
 * 1. EVERY widget callee's id parameter is `u16`, not `s32`
 *    ([[levers.d/merged-callee-signature-oracle]]).  The twin declares
 *    `func_290F60(void *p, u16 id, s32 c, s32 d)` and friends; with `s32` mwcc
 *    re-zero-extends our `u16 id` at each call site and we carried THREE
 *    `andi` retail does not (opscan `andi 1->4`).  -3 words on its own.
 * 2. `f32 *vp = &p->f2D8[i].v;` placed AFTER `b->f06 = b->f06 + 2;`, used
 *    ONLY by `*vp = 0.785f;` in the `t > pi` reset arm.  Retail materialises
 *    `addiu $3,$2,0x2D8` there and still reads/writes `.v` through the
 *    recomputed `p + i*8`.  +3 words, and its POSITION is worth 10 of them
 *    (12 bad after `b->f04`, 11 after `b->f06`... no: 12 / 11 / 2 for the
 *    three positions).
 * 3. `s16 *fp = &p->f2D8[i].f04;` at the LOOP TOP, used ONLY by `*fp = 0;` --
 *    retail's `addiu $16,$3,0x2DC` in a CALLEE-SAVED register.  The guard
 *    still reads the array (`lh $3,0x2DC($3)`), NOT through `fp`; routing the
 *    guard through it is 4 words long.  This is the s27 header's own open
 *    item, which it had priced at +2 and written off.
 * 4. `id++;` (or `id += 1;`) in place of `id = (id + 1) & 0xFFFF;` -- with the
 *    u16 signatures the explicit mask becomes TWO `andi` and no `addiu`;
 *    `id++` gives retail's `addiu $3,$18,0x1` in the f04 guard's `beql` delay
 *    slot plus the single join `andi $18,$3,0xFFFF`.
 * 5. `t = p->f2D8[i].v; t = t + 0.1f;` -- SPLITTING the read from the add is
 *    the last two words: written as one expression, `0.1f` and the `.v` value
 *    trade $f1/$f2.  `f32 step = 0.1f;` as a named local is the other closing
 *    arm (same bytes, different object); the `+` operand order is INERT.
 * ⚠ MEASURED NULLS on the way (a_4eee80{,b,c,d,e,f,g,h}.py, 54 arms): every
 * increment spelling at the OLD s32 signatures (53 or short), `s32`/`u32 id`,
 * the twin's own `id & 0xFFFF` mask-at-use form (56), `R *rp = &p->f2D8[i];`
 * for the whole body (117, a callee-saved rotation), a hoisted `R *base`
 * (117), and the wide pragma screen (pragwide54.log, no cell improves 53).
 */
/* SESSION 29 (2026-09-04): 117 BAD -> 53 at exact length, on the knob plus one
 * declaration move: `#pragma optimization_level 3` (117 -> 56, and it also
 * lowers the mnemonic distance 10 -> 6), then `sy` to position 0 (56 -> 53).
 * The level knob was swept pool-wide in s27, which is where this unit's
 * level-3 column came from; s29 re-decked it AT THE NEW BASE, which is the
 * step s28 records as mandatory once a knob moves the starting point.
 * Deck at the knob base: 86 arms, 4 distinct objects. */
#include "types.h"
/* normal 0x004EEE80 -- DRAFTED s27.  Five 8-byte {f32 phase; s16 live;} records
 * at 0x2D8 are advanced by 0.1 per frame; each live one drives widget `id`
 * (0x74 upward) through func_2907A0/func_2905B0/func_290F60 until its phase
 * passes pi, at which point the record is reset to 0.785 and retired.
 * The gp floats are MAIN `.lit4` POOL entries (t_lit4.retail_words()):
 * -0x772C = 0x0047DA44 = 0.1f, -0x7F74 = 0x0047D1FC = pi,
 * -0x76E0 = 0x0047DA90 = 0.785f, -0x7864 = 0x0047D90C = 0.9f.
 * ORACLE TRANSFER: func_2910A0/func_290460/func_2907A0/func_290F60/func_128FD0
 * signatures from normal_SpaceMenuAnimStep_513000; func_2905B0's four-float shape from
 * MERGED normal_FUN_004EB400.
 *
 * OPEN at the RIGHT LENGTH (124 words), 117 bad, 8 odiff hunks.  What landed:
 * 1. The two `id++` sites are ONE `andi $18,$3,0xFFFF` JOIN at 0x004EF03C, so
 *    the record-dead path and the advance path must both FALL INTO a shared
 *    `id = id + 1` at the bottom of the loop body -- not `continue` after an
 *    inline increment.
 * 2. `id` MUST be `u16` with an explicit `& 0xFFFF` on the sum.  `s32` gives
 *    the right 2-word increment but loses retail's `daddiu $18,$0,0x74` init
 *    ([[mwcc-daddiu-unsigned-narrow]]) AND lets mwcc CSE the literal `0x74` at
 *    the first func_291110 against `id`; it is 4 words SHORT.  `s16` is 4 LONG.
 *    Measured: u16 124 / u32 120 / s32 120 / s16 128 (v_eee80_id.py).
 * 3. The `t > pi` reset arm is the FALL-THROUGH and the advance arm is OUT OF
 *    LINE (`bc1t`), and the `e == NULL` / `b == NULL` exits skip the id++ join.
 * WHAT IS LEFT: retail keeps `addiu $16,$3,0x2DC` -- &p->f2D8[i].f04 -- in a
 * callee-saved register from the LOOP TOP and RECOMPUTES `p + i*8` in the body
 * (`sll $2,$17,3 / addu $2,$19,$2`); we keep `p + i*8` instead and spend one
 * MORE callee-saved register (an extra `sq`/`lq`).
 * ⚠ MEASURED: an explicit `s16 *fp = &p->f2D8[i].f04;` local at the loop top
 * costs +2 words on its own (3 arms, v_eee80_addr.py) -- the DECLARATION is
 * what costs, so this needs the address form without a named local. */

typedef struct R  { f32 v; s16 f04; u8 pad06[2]; } R;      /* 8 */
typedef struct B  { u8 pad00[4]; s16 f04; s16 f06; } B;
typedef struct Res { u8 pad00[0x20]; B *f20; } Res;
typedef struct N  { u8 pad000[0x2D8]; R f2D8[5]; } N;

extern f32   func_128FD0(f32 v);
extern Res  *func_290460(N *p, u16 id);
extern void  func_2905B0(N *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_2907A0(N *p, u16 id, f32 v);
extern void  func_290F60(N *p, u16 id, s32 c, s32 d);
extern void  func_291110(N *p, u16 id, s32 c, s32 d);
extern void  func_2910A0(N *p, s32 id, s32 *x, s32 *y);

void normal_FieldHudAllySuggestRingsUpdate_4eee80(N *p)
{
    s32  sx;
    s32  sy;
    u16  id;
    s32  i;
    Res *e;
    B   *b;
    f32  t;
    f32  u;
    s16 *fp;
    f32 *vp;

    id = 0x74;
    func_2910A0(p, 0x60, &sx, &sy);
    if (sy != 0x12C) {
        if (sy < 0x158 && p->f2D8[0].f04 == 0) {
            func_291110(p, 0x74, 1, 1);
            p->f2D8[0].f04 = 1;
        } else if (sy < 0x13A && p->f2D8[1].f04 == 0) {
            func_291110(p, 0x75, 1, 1);
            p->f2D8[1].f04 = 1;
        }
    }
    for (i = 0; i < 5; i++) {
        fp = &p->f2D8[i].f04;
        if (p->f2D8[i].f04 != 0) {
            e = func_290460(p, id);
            if (e == NULL) {
                continue;
            }
            b = e->f20;
            if (b == NULL) {
                continue;
            }
            b->f04 = b->f04 + 2;
            b->f06 = b->f06 + 2;
            vp = &p->f2D8[i].v;
            t = p->f2D8[i].v;
            t = t + 0.1f;
            p->f2D8[i].v = t;
            if (t > 3.1415927f) {
                *vp = 0.785f;
                b->f04 = 0x22;
                b->f06 = 0x22;
                *fp = 0;
                func_291110(p, id, 0, 1);
                continue;
            }
            u = func_128FD0(t);
            func_2907A0(p, id, u);
            func_2905B0(p, id, 0.9f + u, 0.9f + u, 0.9f + u, -1.0f);
            func_290F60(p, id, 0x3F, sy + 0x19);
        }
        id++;
    }
}
