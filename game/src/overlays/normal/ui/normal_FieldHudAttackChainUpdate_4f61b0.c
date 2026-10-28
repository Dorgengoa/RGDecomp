/* rgp:protos */
#define RGP_SELF_normal_FieldHudAttackChainUpdate_4f61b0 1
#include "port/game_protos.h"
#line 1
/* === SESSION 68 (2026-09-20, SOLO): MATCH, MERGED.  449 bad -> 0.  The unit
 * had never been read against the listing -- s31's automated decks moved two
 * statements into it and nobody ever checked the body.  NINE edits, every one
 * found by reading retail straight through.  Sweeps: build/wf-normal/s68/d*.py,
 * e*.py.  ⚠ Eight of the nine are INERT OR NEGATIVE ALONE; this is a nine-way
 * cross, and the last two edits alone are worth 36 -> 17 -> MATCH.
 *
 *  1. In the `f3E4 == 1` arm the `f = p->f3E8 + D_0047DA9C;` add belongs
 *     BELOW the func_28F2B0 / `if (w != 0)` block, not above it.  Above it,
 *     the live float forces a CALLEE-SAVED FPR (`swc1 $f20` in the prologue)
 *     that retail does not have.
 *  2. ★ THE CLAMP IDIOM, three times (f3E4==1, f3DC==0x21, f3DC==0x16).
 *     Retail wants THREE fp temps live at the compare -- $f2 = the old field,
 *     $f1 = the delta/result, $f0 = the limit -- and the `swc1` in the
 *     `bc1t` DELAY SLOT.  The only spelling that gives all of that is
 *         t = p->f3E0;  f = t + DELTA;  lim = D_0047D1FC;  p->f3E0 = f;
 *         if (!(f <= lim)) { ... }
 *     i.e. the field READ IS ITS OWN STATEMENT and `lim` is created THIRD.
 *     `lim` first is one word short; `lim` last is one word long; inlining
 *     `D_0047D1FC` at the compare is one word long; naming only the delta is
 *     inert.  Worth 57 -> 36 across the three sites (7 words each).
 *     ⚠ The f32 DECLARATION ORDER is a clean null -- all six permutations of
 *     `f`/`t`/`lim` are ONE OBJECT.  These are TEMPS; only the statement
 *     order moves them ([[levers.d/mwcc-vreg-creation-source-position]]).
 *  3. `f3DC == 3`'s clamp is the OTHER shape: `p->f3E0 = f;` unconditionally
 *     and then `if (!(f < 1.0f)) p->f3E0 = 1.0f;`.  The if/else form emits
 *     `bc1fl` where retail has `bc1t`.
 *  4. `w->f40 = (s32)a / 2;` -- THE REDUNDANT CAST IS LOAD-BEARING.  Retail
 *     computes the signed divide `a / 2` TWICE (0x004F646C and 0x004F64B4/
 *     0x004F64DC): the first copy's register is clobbered by `lui $3,0x4250`
 *     and mwcc rematerialises it.  A plain `a / 2` is CSE'd against the
 *     `-(a / 2)` above and is FOUR WORDS SHORT; `(s32)a` breaks the value
 *     number and buys the whole second idiom back.  `a >> 1` buys only one
 *     word, `(u32)a / 2` one, `-(-a / 2)` two, `(long)a / 2` six,
 *     `(a + 0) / 2` / `a / (s32)2` / `(s32)(a / 2)` / `a / 2 + 0` are all the
 *     plain form.  Same family as [[levers.d/mwcc-identity-cast-splits-cse]]
 *     and s67's ADDEND cast.
 *  5. `-(a / 2)` must be a NAMED local (`h`), shared by `w->f00` and
 *     `w->f20`; written twice inline mwcc emits `addu`+`negu`+`negu` where
 *     retail has `negu`+`subu` and REUSES $6.  ⚠ `h` must be its OWN name --
 *     reusing the `x` that the f3DC==0x21 block uses is 61 bad, a separate
 *     `h` is 57.
 *  6. ★★ THE LAST EDIT, 17 -> MATCH: `b = (s32)(31.0f - 24.0f * t);` goes
 *     ABOVE `w->f04 = (s32)(52.0f * t);`, not below it.  Retail's caller-saved
 *     pair is b=$7 / h=$6; with `b` computed after `h` (or after the f04
 *     store) we get b=$6 / h=$7 and mwcc also INTERLEAVES the two multiplies
 *     instead of serialising them.  Below the f04 store is 17 bad, above it
 *     is MATCH -- one statement, and the b/h ORDER alone (36 -> 17) is not
 *     enough.
 *  7. `w->f44` is stored BEFORE `w->f42` and `w->f40` (retail emission order
 *     0x44, 0x42, 0x40, 0x46); with f40/f42/f44 in address order mwcc cannot
 *     start the f44 multiply early enough and pays two `nop`s (+1 word).
 *  8. `w->f44` reads `p->f3E0` again, NOT `t`.
 *  9. `t` must be named for the a/f04/b group: without it mwcc RELOADS
 *     `p->f3E0` for the `msub.s`, +1 word.
 *
 * ARMING: n_olink.py relinks NORMAL.BIN BYTE-IDENTICAL with this unit
 * compiled, and `w->f0E = 0x1A` -> `0x1B` gives exactly 1 differing byte at
 * vram 0x004F6638. */
#include "types.h"
/* normal 0x004F61B0 -- session 31 lane a8, FRESH.
 * The intro/outro animation driver for the 0x14 sub-widget of `p`.
 * f3DC is the outer state, f3E4 the inner (fade-in) sub-state, f3E0 and
 * f3E8 the two 0..1 timelines.  Each state advances its timeline by a gp
 * float, clamps it, and re-lays the widget's s16 boxes from it.
 *
 * The `.word 0x46000024` entries are cvt.w.s -- float->int casts, not data
 * ([[asm-listing-word-mnemonics]]).
 * `adda.s $f0,$f1 / msub.s $f0,$f2,$f3` off an `mtc1 $0,$f0` is the PS2
 * accumulator spelling of `A - B*t`; `madd.s` is `A + B*t`
 * ([[ps2-float-accumulator]]).
 * `bgez/addiu 1/sra 1` is a SIGNED divide by 2.
 * gp base is 0x00485170 (D_00484454 = gp-0xD1C in merged normal_BtlChgMenuCommandDispatchState_500b80).
 */

typedef struct W {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x0E - 0x08];
    s16 f0E;
    u8  pad10[0x1C - 0x10];
    s16 f1C;
    s16 f1E;
    s16 f20;
    s16 f22;
    s16 f24;
    s16 f26;
    u8  pad28[0x2E - 0x28];
    s16 f2E;
    u8  pad30[0x40 - 0x30];
    s16 f40;
    s16 f42;
    s16 f44;
    s16 f46;
    u8  pad48[0x6E - 0x48];
    s16 f6E;
    u8  pad70[0x8E - 0x70];
    s16 f8E;
} W;

typedef struct Obj {
    u8  pad000[0x14];
    u8  f014[0x3DC - 0x14];
    s16 f3DC;
    u8  pad3DE[2];
    f32 f3E0;
    s16 f3E4;
    u8  pad3E6[2];
    f32 f3E8;
} Obj;

extern f32 D_0047D1FC;            /* gp - 0x7F74 */
extern f32 D_0047D5D0;            /* gp - 0x7BA0 */
extern f32 D_0047D904;            /* gp - 0x786C */
extern f32 D_0047DA8C;            /* gp - 0x76E4 */
extern f32 D_0047DA9C;            /* gp - 0x76D4 */
extern f32 D_0047DAA0;            /* gp - 0x76D0 */
extern f32 D_0047DAA4;            /* gp - 0x76CC */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudAttackChainUpdate_4f61b0(Obj *p)
{
    W  *w;
    f32 f;
    f32 t;
    f32 lim;
    s32 a;
    s32 b;
    s32 c;
    s32 x;
    s32 h;
    s32 y;
    s32 z;

    if (p->f3DC == 0) {
        return;
    }
    if (p->f3E4 > 0) {
        if (p->f3E4 == 1) {
            w = ((W *)UiGetWidgetSubItem_28f2b0(p->f014, 2, 0));
            if (w != 0) {
                w->f00 = -0x48;
                w->f02 = -0x64 - (s32)(32.0f * Sinf_128fd0(p->f3E8));
                w->f1C = 0x32;
                w->f1E = 0x41;
            }
            t = p->f3E8;
            f = t + D_0047DA9C;
            lim = D_0047D1FC;
            p->f3E8 = f;
            if (!(f <= lim)) {
                p->f3E4 = p->f3E4 + 1;
                p->f3E8 = 1.0f;
            }
        }
        if (p->f3E4 == 2) {
            f = p->f3E8 - D_0047D5D0;
            p->f3E8 = f;
            if (f <= 0.0f) {
                p->f3E4 = p->f3E4 + 1;
                p->f3E8 = 1.0f;
            }
        }
        if (p->f3E4 == 3) {
            f = p->f3E8 - D_0047DAA0;
            p->f3E8 = f;
            if (f <= 0.0f) {
                p->f3E8 = 0.0f;
                p->f3E4 = 0;
            }
            w = ((W *)UiGetWidgetSubItem_28f2b0(p->f014, 2, 0));
            if (w != 0) {
                w->f00 = (s32)-(72.0f * p->f3E8);
                w->f02 = (s32)-(100.0f * p->f3E8);
                w->f1C = (s32)(30.0f * p->f3E8) + 0x14;
                w->f1E = (s32)(39.0f * p->f3E8) + 0x1A;
            }
        }
    }
    if (p->f3DC == 1) {
        f = p->f3E0 + D_0047DAA0;
        p->f3E0 = f;
        if (!(f < 1.0f)) {
            p->f3E0 = 1.0f;
        }
        UiSetWidgetAlpha_2907a0(p->f014, 2, 1.5f * p->f3E0);
        w = ((W *)UiGetWidgetSprite_28fe10(p->f014, 1, 0));
        if (w != 0) {
            t = p->f3E0;
            a = (s32)(280.0f * t);
            b = (s32)(31.0f - 24.0f * t);
            w->f04 = (s32)(52.0f * t);
            h = -(a / 2);
            w->f00 = h - w->f04;
            w->f02 = -b / 2;
            w->f06 = b;
            w->f20 = h;
            w->f22 = -b / 2;
            w->f24 = a;
            w->f26 = b;
            w->f44 = (s32)(52.0f * p->f3E0);
            w->f42 = -b / 2;
            w->f40 = (s32)a / 2;
            w->f46 = b;
            w->f6E = 0;
            w->f8E = 0;
        }
        if (!(p->f3E0 < 1.0f)) {
            p->f3DC = 2;
            UiSetWidgetAlpha_2907a0(p->f014, 2, 1.0f);
            p->f3E0 = 0.0f;
        }
    }
    if (p->f3DC == 2) {
        f = p->f3E0 + D_0047D904;
        p->f3E0 = f;
        if (!(f < 1.0f)) {
            p->f3DC = 3;
            p->f3E0 = 0.0f;
        }
    }
    if (p->f3DC == 3) {
        f = p->f3E0 + D_0047DAA0;
        p->f3E0 = f;
        if (!(f < 1.0f)) {
            p->f3E0 = 1.0f;
        }
        UiSetWidgetPos_290f60(p->f014, 2, (s32)(-43.0f + 97.0f * p->f3E0), -0x1C);
        w = ((W *)UiGetWidgetSprite_28fe10(p->f014, 1, 3));
        if (w != 0) {
            c = (s32)(26.0f * p->f3E0);
            w->f06 = c;
            w->f02 = -((s16)c / 2);
            w->f0E = 0x1A;
            c = (s32)(26.0f * p->f3E0);
            w->f26 = c;
            w->f22 = -((s16)c / 2);
            w->f2E = 0x1A;
        }
        if (!(p->f3E0 < 1.0f)) {
            p->f3DC = 0x14;
            p->f3E0 = 1.0f;
        }
    }
    if (p->f3DC == 0x21) {
        t = p->f3E0;
        f = t + D_0047DAA4;
        lim = D_0047D1FC;
        p->f3E0 = f;
        if (!(f <= lim)) {
            p->f3DC = 0x2B;
            p->f3E0 = lim;
        }
        x = -(s32)(20.0f * Sinf_128fd0(p->f3E0));
        y = -(s32)(10.0f * Sinf_128fd0(p->f3E0));
        z = (s32)(40.0f * Sinf_128fd0(p->f3E0)) + 0x7C;
        UiSetSpritePosSize_28fd70(p->f014, 4, x, y, z,
                    (s32)(20.0f * Sinf_128fd0(p->f3E0)) + 0x1F, 0);
        UiSetWidgetPos_290f60(p->f014, 4, -0x3E,
                    -0x48 - (s32)(64.0f * Sinf_128fd0(p->f3E0)));
    }
    if (p->f3DC == 0x16) {
        t = p->f3E0;
        f = t + D_0047DA8C;
        lim = D_0047D1FC;
        p->f3E0 = f;
        if (!(f <= lim)) {
            p->f3DC = 0x20;
            p->f3E0 = lim;
        }
        x = -(s32)(16.0f * Sinf_128fd0(p->f3E0));
        y = -(s32)(8.0f * Sinf_128fd0(p->f3E0));
        z = (s32)(32.0f * Sinf_128fd0(p->f3E0)) + 0x46;
        UiSetSpritePosSize_28fd70(p->f014, 3, x, y, z,
                    (s32)(16.0f * Sinf_128fd0(p->f3E0)) + 0x1F, 0);
    }
}
