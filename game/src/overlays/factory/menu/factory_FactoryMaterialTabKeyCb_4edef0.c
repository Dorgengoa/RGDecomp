/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialTabKeyCb_4edef0 1
#include "port/game_protos.h"
#line 1
/* SESSION 37, lane fg37f -- CLOSED, BYTE-IDENTICAL (was 2 bad, 76 words).
 * THE CLOSE IS ONE TOKEN: `s32 cur` -> `s64 cur`.
 * The residue was 0x004EDF40 / 0x004EDF94 (`addiu $2,$17,-1` / `addiu
 * $2,$17,1` retail, ours `$16`), a pure s0<->s1 substitution.  BOTH objects
 * emit the copy `daddu $17,$16,$0`; the defect was that mwcc FORWARD-
 * SUBSTITUTED the copy at the two arithmetic reads of `v` and retail did not.
 * Widening `cur` to s64 makes `v = cur` a NARROWING CONVERSION instead of a
 * plain copy, and mwcc does not propagate a conversion -- the two `addiu`
 * then read $17.  Everything else (the `lh $16,0x4($2)` load, the three
 * `(s16)cur` dsll32/dsra32 compares, the length) is unchanged.
 * BOUNDARY measured the same run: `s16 cur` is LENGTH-BREAKING (-6 words,
 * len 0x118 vs 0x130) with or without the (s16) casts -- the narrowing
 * direction is what pays, not merely `a type other than s32`.
 */

#include "types.h"

/* factory.bin overlay, 0x004EDEF0 -- 76 words, EXACT LENGTH, 2 bad.  PARKED.
 *
 * RESIDUE, 0x004EDF40 / 0x004EDF94:
 *   ours   2602FFFF addiu $2,$16,-0x1   26020001 addiu $2,$16,0x1
 *   retail 2622FFFF addiu $2,$17,-0x1   26220001 addiu $2,$17,0x1
 * $16 = cur (lh $16,0x4($2)), $17 = v (daddu $17,$16,$0).  mwcc forward-
 * substitutes the copy `v = cur` and reads cur; retail reads v.
 *
 * THE MECHANISM IS MEASURED, and it is symmetric -- mwcc rewrites every use of
 * a copy's DESTINATION to its SOURCE, for as long as the copy is available:
 *   `cur = load; v = cur;`  -> uses of v become $16  (the 2 bad words here)
 *   `v = load; cur = v;`    -> uses of cur become $17 (2 bad words, but at
 *                              0x4EDF30/0x4EDF80 -- the inner (s16)cur
 *                              compares -- with the two addiu now CORRECT).
 * The two variants are exactly COMPLEMENTARY; retail needs the compares on
 * $16 and the arithmetic on $17, which no single copy direction gives.
 *
 * INERT (byte-identical to the baseline object): re-reading D_00484A58->f04
 * into v instead of copying cur; `cur ^ 0`, `cur | 0`, `cur * 1`, `cur + 0`,
 * `-(-cur)`, `cur ? cur : cur`; `(s16)(v + -1)`; a scratch `t = v; v = (s16)
 * (t - 1);`; a dead `v = 0;` at the tail; a dead `cur = v;` after the stores;
 * swapping the cur/v declaration order; `s16 v` with the (s16) casts either
 * kept or dropped (that pair IS a distinct object, still 2 bad, but it reads
 * $2 -- the compare's own sign-extension temp -- so it is further away).
 * WORSE: re-reading the global in the inner compares (6 bad); a `Head *h`
 * handle (59); `const s32 cur = ...` (21).  LENGTH-BREAKING: `(s32)(s16)cur`
 * (-3 words); an `s32 vv[1]` holder (+10); distributing `v = cur` into the
 * arms (+6); re-reading the global in every compare (-3).
 */

typedef struct Head {
    u8  pad00[0x4];
    s16 f04;
} Head;

extern Head *D_00484A58;                        /* _gp - 0x718 */
extern u8    D_004B2570[0x10];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialTabKeyCb_4edef0(void)
{
    void *m;
    s64   cur;
    s32   v;

    m = SceneSoundGetSlot0HandleCur_207df0();
    cur = D_00484A58->f04;
    v = cur;
    if (PadIsTriggered_1839f0(D_004B2570, 4) != 0) {
        if ((s16)cur > 0) {
            v = (s16)(v - 1);
        } else if (PadIsRepeatTriggered_183dd0(D_004B2570, 4) == 0) {
            v = 4;
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 8) != 0) {
        if (4 > (s16)cur) {
            v = (s16)(v + 1);
        } else if (PadIsRepeatTriggered_183dd0(D_004B2570, 8) == 0) {
            v = 0;
        }
    }
    if ((s16)cur != (s16)v) {
        SoundPlayScaledVolume_1b9520(m, 0xB, 0, 1.0f);
        D_00484A58->f04 = v;
        factory_FactoryMaterialTabHighlight_4f3740(D_00484A58);
        factory_FactoryMaterialShowCellInfo_4f38f0(D_00484A58);
    }
    return 1;
}
