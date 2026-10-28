/* rgp:protos */
#define RGP_SELF_normal_FieldHudAllySuggestTimerUpdate_4eea90 1
#include "port/game_protos.h"
#line 1
/* CONFIRMED BYTE-IDENTICAL 2026-08-30, lane nu07 (batch D1), 500 B / 125 words,
 * scored with build/dv_oslit_nu07.py (dv_osbuild + the scripts/t_lit4.py pool
 * retarget): row `normal_FieldHudAllySuggestTimerUpdate_4eea90  125  MATCH  lit4:ok/2`.
 *
 * WHAT KILLED THE 6-WORD RESIDUE: D_0047D35C is an mwcc `.lit4` POOL ENTRY
 * (1.9f), not a gp global.  Written `extern f32 D_0047D35C` the load is pinned
 * and mwcc emits the `mtc1 $2,$f15` at lui+1 at BOTH func_2905B0 call sites
 * where retail emits it at lui+3 (6 bad words, object 03b1604b, 43 prior
 * spellings all inert).  Written as the LITERAL `1.9f` the schedule is
 * retail's exactly (object a90293de; the 2 remaining "bad" words are the two
 * `lwc1` displacements the plain scorer cannot resolve -- the .lit4 scorer gap,
 * closed by the retarget).
 * D_0047D90C (0.9f) and D_0047DA84 (-0.045f) must STAY externs: the literal
 * for either one alone is 8 bad (d2d30aae / 334df1b2), i.e. the
 * literal-vs-extern axis is live in BOTH directions inside ONE function.
 * `#pragma usefloatacc off` is INERT here (object 03b1604b = baseline).
 */
#pragma divbyzerocheck on
#include "types.h"
/* normal 0x004EEA90 -- the panel's 30-frame blink tick.  f3A4 is the frame
 * counter: `5 - f3A4/30` drives the two 0x63/0x64 markers' x offset, every
 * 15th frame the 0x68 marker's x toggles between 0x6E and 0x8C, and every
 * 30th frame the whole 0x61/0x63 pair is re-coloured.
 *
 * `dsll32/dsra32 ..,16` off the `subu` is an s32 local with an explicit
 * `(s16)` cast (an s16 local is a measured null).  `% 30` and `% 15` are bare
 * `div`s; only the `/ 30` at the top carries the `bnez`/`break 0,7` pair.
 *
 * PARKED (WF40 lane div-small, 2026-08-26) at 6 bad words of 125; the word
 * total EQUALS the declared 0x1F4/4, so the measurement is sound.  Residue is a
 * pure SCHEDULER rotation of three ready instructions at BOTH func_2905B0 call
 * sites, and nowhere else:
 *   retail 004EEBD4 daddu $4,$19,$0 / 004EEBD8 addiu $5,$0,0x61
 *          004EEBDC mtc1  $2,$f15
 *   ours   004EEBD4 mtc1  $2,$f15   / 004EEBD8 daddu $4,$19,$0
 *          004EEBDC addiu $5,$0,0x61
 *   and identically at 004EEC18/1C/20 for the 0x63 call.
 * The two func_2904E0 blocks -- same shape plus one extra `lwc1 $f16` -- are
 * BYTE-IDENTICAL, so mwcc places the mtc1 at the same rank as retail whenever
 * one more instruction is available to fill the lui->mtc1 gap; with the shorter
 * 6-argument list it emits mtc1 at lui+1 and retail emits it at lui+3.
 *
 * 43 spellings measured in two one-round-trip sweeps (build/na07_vea90.py,
 * build/na07_vea90b.py); 41 produced the IDENTICAL object 03b1604b:
 *   func_2905B0 id as s32/s16/u32/s64/u8, both callees id s32, func_2904E0 id
 *   s16, first parameter Obj* / const void*, return type s32, `1.0` double
 *   literal, `(f32)1`, a named `f32 one` local, a named `f32 col` local for the
 *   three equal float arguments, swapping the two extern declarations, an extra
 *   live local, a local copy of `p`, and ALL 23 permutations of the four local
 *   declarations -- every one of those 41 is an INERT cell.
 * Only two arms moved the object at all and both are WORSE: `f64 d` on
 * func_2905B0 (52039b57, 8 bad words) and inverting the loop's if/else
 * (d92d42c6, 0x1F8 vs 0x1F4 -- which confirms `if (a > 0)` is the right
 * polarity).  Type, spelling and declaration order are a MEASURED NULL here. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3A4 - 0x37A];
    s16 f3A4;
} Obj;

typedef struct W { u8 pad00[0x08]; s16 f08; s16 f0A; } W;
typedef struct H { u8 pad00[0x20]; W *f20; } H;

extern void *D_00484410;          /* gp - 0xD60  */
extern f32   D_0047D90C;          /* gp - 0x7864 */
extern f32   D_0047DA84;          /* gp - 0x76EC */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_FieldHudAllySuggestTimerUpdate_4eea90(Obj *p);

void normal_FieldHudAllySuggestTimerUpdate_4eea90(Obj *p)
{
    H  *h;
    W  *w;
    s32 a;
    s32 i;

    if (p->f378 == 0) {
        return;
    }
    a = (s16)(5 - p->f3A4 / 30);
    for (i = 0; i < 2; i++) {
        h = ((H *)UiFindWidget_290460(p, i + 0x63));
        if (h == 0) {
            return;
        }
        w = h->f20;
        if (w == 0) {
            return;
        }
        if (a > 0) {
            w->f08 = (a - i) * 24;
        } else {
            w->f08 = a * 24;
        }
    }
    if (p->f3A4 % 15 == 0) {
        h = ((H *)UiFindWidget_290460(p, 0x68));
        if (h == 0) {
            return;
        }
        w = h->f20;
        if (w == 0) {
            return;
        }
        if (w->f0A == 0x6E) {
            w->f0A = 0x8C;
        } else if (w->f0A == 0x8C) {
            w->f0A = 0x6E;
        }
        if (p->f3A4 % 30 == 0) {
            SoundPlayScaledVolume_1b9520(D_00484410, 0x1C, 0, 1.0f);
            UiSetWidgetColor_2905b0(p, 0x61, 1.9f, 1.9f, 1.9f, 1.0f);
            UiFadeWidgetColor_2904e0(p, 0x61, D_0047D90C, D_0047D90C, D_0047D90C, 1.0f,
                        D_0047DA84);
            UiSetWidgetColor_2905b0(p, 0x63, 1.9f, 1.9f, 1.9f, 1.0f);
            UiFadeWidgetColor_2904e0(p, 0x63, D_0047D90C, D_0047D90C, D_0047D90C, 1.0f,
                        D_0047DA84);
        }
    }
    UiSetWidgetAlpha_2907a0(p, 0x63, 1.0f);
}
