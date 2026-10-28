/* rgp:protos */
#define RGP_SELF_normal_FieldHudRadarReset_4f17c0 1
#include "port/game_protos.h"
#line 1
/* === SESSION 64 (2026-09-15, SOLO): CLOSED, 60 bad -> BYTE-IDENTICAL.
 * s42's two-edit cross was right and s54 named both halves; what was missing
 * was the -2 half.  Five edits, in the order they were measured:
 *   1. -2 WORDS: split the `*func_290460(p, b)->f20 = -1;` store into a named
 *      pointer local.  That alone is 91 words (retail 93) -- the first arm on
 *      this unit ever to go SHORT, and the partner s42/s54 could not find.
 *   2. +2 WORDS: `a = 0x4A; b = 0x2E;` BEFORE the loop (the s42 fix that was
 *      always +2 alone) and the dead tail assignments deleted.  60 -> 23.
 *   3. DECLARATION ORDER `s32 i; u16 a; u16 b;` -- 23 -> 13, and it fixes the
 *      whole callee-saved map at once (retail b=$18 a=$19 i=$20 p=$21; with
 *      `a,b,i` declared we emitted i=$18 b=$19 a=$20, the REVERSE).
 *      See memory/levers.d/mwcc-gpr-decl-order-map.md.
 *   4. `a++; b++;` moved to the very END of the loop body, after both
 *      `p->f438[i]`/`p->f47C[i]` stores -- 13 -> 4.  Every other placement of
 *      the two increments measured 13-15.
 *   5. `Ret *r = func_290460(p, b); *r->f20 = -1;` instead of an `s16 *q`
 *      pointing at `->f20` -- 4 -> MATCH.  The residue at 4 was q and the -1
 *      holding each other's caller-saved register ($5/$6 swapped); NOTHING
 *      else reached it (12 decl-order arms for q and an explicit `m1` local
 *      are all BYTE-IDENTICAL, and so are 17 of 19 armed pragmas).  Naming the
 *      RETURNED STRUCT rather than the member it loads creates the pointer web
 *      one step earlier and it takes $5.
 * !! Arming: `#pragma opt_unroll_count off` fails to build (it takes a number),
 * `opt_propagation off` / `opt_common_subs off` / `opt_loop_invariants off` /
 * `opt_rotateloops off` are all length-wrong -- the pragma deck discriminates.
 * * The unit was found by re-running memory/levers.d/opcode-histogram-screen.md
 * over the CURRENT 48-unit open list: `daddiu:2->0` put it at the top.
 * SESSION 42/54 history is in git; the two words they named (our duplicated
 * `sll` in the bnezl slot, our `move v1,s5` copying the -1 out of a
 * callee-saved register) are BOTH gone -- edit 1 removed them together, so
 * neither was a separate defect.  Arms: build/wf-normal/s64/v17c0*.py
 */
#include "types.h"
/* normal 0x004F17C0 -- widget reset: four fixed slots, then five rows whose
 * two slot ids walk upward.  `daddiu $19, $0, 0x4A` and the `andi ..,0xFFFF`
 * after every increment are the tell that both counters are REGISTER-RESIDENT
 * u16 ([[mwcc-daddiu-unsigned-narrow]]), not s32. */
typedef struct Ret {
    u8   pad000[0x20];
    s16 *f20;
} Ret;

typedef struct N {
    u8  pad000[0x434];
    s32 f434;
    s32 f438[5];
    u8  pad44C[0x478 - 0x44C];
    s16 f478;
    s16 f47A;
    s16 f47C[5];
    u8  pad486[0x4AC - 0x486];
    s32 f4AC[5];
    s32 f4C0[(0x4EC - 0x4C0) / 4];
    s32 f4EC;
    s32 f4F0;
    s32 f4F4;
} N;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudRadarReset_4f17c0(N *p)
{
    s32 i;
    u16 a;
    u16 b;

    UiSetWidgetAlpha_2907a0(p, 0x3F, 1.0f);
    UiSetWidgetsVisibleById_291110(p, 0x3F, 0, 1);
    UiSetWidgetAlpha_2907a0(p, 0x25, 1.0f);
    UiSetWidgetsVisibleById_291110(p, 0x25, 0, 1);
    p->f4EC = 0;
    p->f434 = 0;
    a = 0x4A;
    b = 0x2E;
    for (i = 0; i < 5; i++) {
        p->f4AC[i] = 0;
        UiSetWidgetsVisibleById_291110(p, a, 0, 1);
        UiSetWidgetsVisibleById_291110(p, a - 5, 0, 1);
        UiSetWidgetsVisibleById_291110(p, a - 10, 0, 1);
        UiSetWidgetAlpha_2907a0(p, b, 0.0f);
        UiSetWidgetsVisibleById_291110(p, b, 0, 1);
        {
            Ret *r = ((Ret *)UiFindWidget_290460(p, b));
            *r->f20 = -1;
        }
        p->f438[i] = 0;
        p->f47C[i] = 0;
        a++;
        b++;
    }
    p->f478 = 0;
    p->f47A = 0;
    p->f4F0 = -1;
    p->f4F4 = 0;
}
