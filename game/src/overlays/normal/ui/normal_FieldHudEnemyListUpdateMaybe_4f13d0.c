/* rgp:protos */
#define RGP_SELF_normal_FieldHudEnemyListUpdateMaybe_4f13d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* === SESSION 65 (2026-09-15, SOLO): 7 -> MATCH, and s62's verdict below is
 * REFUTED.  The residue was NOT caller-saved register identity, it was the
 * [[at-compare-class]] OPERATOR SPELLING, on both guards:
 *     if (o->f47C[i] >= 0x15)   ->   if (o->f47C[i] > 0x14)
 *     if (o->f47C[i] >= 0x10)   ->   if (o->f47C[i] > 0xF)
 * `>= K` puts the slti in a GPR, `> K-1` puts it in $at -- and the $at form
 * ALSO reorders the address/load pair, so retail's `addiu s6,v1,0x47C`
 * followed by the self-overwriting `lh v1,0x47C(v1)` falls out of the same
 * edit.  All seven words in ONE two-token change.
 * ⇒ SCREEN FOR THIS FIRST: build/wf-normal/s65/atscan.py counts compares
 * whose destination is $at in retail vs in our object, per unit.  It was
 * armed on 25 merged units (0 rows) and printed a row for nine open units.
 */
/* === SESSION 62 (2026-09-15, SOLO): closed the 2-word LENGTH gap this unit
 * had been stuck on since session 31 (~30 sessions). Acted on s61's own
 * "untried" line: gave id5 and id10 each a dedicated `u16 id5m`/`u16 id10m`
 * local, scoped right where the row-counter branch's three same-value call
 * sites are (`func_290F50`/`func_290770`/`func_291110`), instead of letting
 * each call site re-narrow `id5`/`id10` from s32 independently. Retail keeps
 * ONE `andi $reg,$reg,0xFFFF` per id5/id10 sub-block and reuses the masked
 * register across all three calls (confirmed by reading the retail listing
 * directly: words 121/144 `andi s0,s0,-1` / `andi s0,s5,-1`, both DUPLICATED
 * across the branch-likely join per [[levers.d/mwcc-branch-likely-duplication]],
 * feed words 125/132/138 unmasked); a plain `s32 id5`/`id10` re-narrows at
 * every one of those three call sites instead. The named local reproduces
 * retail's one-mask-per-block shape exactly: **218 words (exact length,
 * matches retail's 220 minus 2 trailing alignment nops) and 218/218 -> 7 bad**
 * (was 216 words, LENGTH-WRONG, since s31).
 * The remaining 7 bad words are a NEW, separate, well-characterized residue
 * in the `c = &o->f47C[i]; if (o->f47C[i] >= 0x15)` guard read (addresses
 * 004F1538-004F1548 and the mirrored second compare at 004F1670): retail
 * computes the address (`addiu s6,v1,0x47C`) BEFORE the load and reuses v1
 * itself as the load's destination (`lh v1,0x47C(v1)`, self-overwrite,
 * `slti at,v1,...`), while ours loads into a0 first and keeps the addiu
 * second (`slti v1,a0,...`). Pure caller-saved register identity, not an
 * expression-spelling difference: s61's own `*c` swap for this exact guard
 * is confirmed STILL inert on top of today's fix, and two fresh decl-order
 * permutations of `c`/`px`/`py`/`y` (both before and after `i`/`id5`/`id10`)
 * are also both null -- expected, since `c`'s address register (s6) is
 * callee-saved and already correctly assigned; the two DISAGREEING registers
 * (the loaded value and the slti destination) are caller-saved temps, which
 * the project's decl-order levers govern for callee-saved webs, not these.
 * NEXT: this needs whatever decides caller-saved temp identity at a load+
 * compare site with no competing live range named yet -- not a spelling this
 * session's arms could reach. */
/* === SESSION 61 (2026-09-15, SOLO): still 2 words SHORT (216 vs retail 220,
 * 0x360 vs 0x368 -- odiff's trailing `retail[218:220] nop nop` hunk is
 * inter-function alignment padding after `jr $31`, not part of this unit's
 * body, so the real gap is the two 16-vs-17-word hunks at 004F1598/004F15F4).
 * Tried the one new idea this unit's own typing note suggests: read the row's
 * counter through the already-computed pointer (`*c >= 0x15` instead of
 * `o->f47C[i] >= 0x15`, `c` declared the line above) to match retail's
 * `addiu $22,...,0x47C` immediately followed by `lh $3,0x47C($3)` at 004F1538
 * -- BYTE-IDENTICAL to the baseline (mwcc already CSEs the address whether
 * the guard is spelled through `c` or through `o->f47C[i]`; `c`'s domination
 * makes the two spellings equivalent). The real 2-word gap is inside the
 * id/id5 per-call `andi` pattern this file's own header already named
 * (retail's second `func_291110(id5,...)` call CSEs its `& 0xFFFF` mask into
 * $16 across BOTH the `<=0.0f` guard's call and the following `id5-`-derived
 * work; ours re-masks). This is a live-range/CSE fact matching session 31's
 * combined-deck sweep's own documented shape for this unit family, not a
 * plain statement-order or pointer-vs-index spelling -- no arm from either
 * axis was found this session. Untried: forcing `id5`'s mask into a named
 * local shared by both its call sites, the way the header describes id10
 * NOT getting the same CSE for a reason not yet explained either. */
/* normal 0x004F13D0 -- session 31 lane n31c, FRESH.
 * Per-row refresh of the 0x4A.. widget triple (id, id-5, id-10) for each of
 * o->f47A rows: enables/disables the three widgets from func_290770's phase,
 * scrolls the row in while its counter is under 0x15, and clears the f382
 * "dirty" flag once every widget of every row has finished.
 *
 * TYPING, read off the andi pattern ([[mwcc-daddiu-unsigned-narrow]]):
 * `id` is u16 -- it is passed to the u16 parameters with NO `andi`, and
 * reading it into an int expression is what emits `andi $21,$18,0xFFFF`;
 * `id5`/`id10` are s32 -- they are narrowed AT EVERY CALL, and the second
 * block CSEs that narrowing into $16.  `((x & 0xFFFF) + 1) & 0xFFFF` folds,
 * which is why `id++` has no read-side andi. */

typedef struct Obj {
    u8  pad000[0x382];
    u8  f382;
    u8  pad383[0x430 - 0x383];
    u8  f430;
    u8  pad431[0x47A - 0x431];
    s16 f47A;
    s16 f47C[16];
} Obj;

extern f32 D_0047D94C;            /* gp - 0x7824 */
extern f32 D_0047DA80;            /* gp - 0x76F0 */
extern f32 D_0047DA84;            /* gp - 0x76EC */
extern f32 D_0047DA88;            /* gp - 0x76E8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudEnemyListUpdateMaybe_4f13d0(Obj *o)
{
    s32 cnt;
    u16 id;
    s32 i;
    s32 id5;
    s32 id10;
    s32 y;
    s16 *c;
    s32 px;
    s32 py;

    switch (o->f430) {
    case 2:
        normal_FieldHudRadarFadeInCheck_4f1380(o);
        break;
    }
    if (o->f382 == 0) {
        return;
    }
    cnt = 0;
    id = 0x4A;
    for (i = 0; i < o->f47A; i++) {
        if (UiGetWidgetAlpha_290770(o, id) > 0.0f) {
            UiSetWidgetsVisibleById_291110(o, id, 1, 1);
            id5 = id - 5;
            UiSetWidgetsVisibleById_291110(o, id5, 1, 1);
            id10 = id - 10;
            UiSetWidgetsVisibleById_291110(o, id10, 1, 1);
        } else {
            UiSetWidgetsVisibleById_291110(o, id, 0, 1);
            id5 = id - 5;
            UiSetWidgetsVisibleById_291110(o, id5, 0, 1);
            id10 = id - 10;
            UiSetWidgetsVisibleById_291110(o, id10, 0, 1);
        }
        UiGetWidgetPos_2910a0(o, id, &px, &py);
        if (px < 0x19B) {
            UiMoveWidgetUniform_290f50(o, 0x4F, 0, -0x34, D_0047D94C, 0);
        }
        if (px < 0xA1) {
            c = &o->f47C[i];
            if (o->f47C[i] > 0x14) {
                y = i * 30 + 0xB4;
                UiMoveWidgetUniform_290f50(o, id, -0xA0, y, 28.0f, 1);
                if (UiGetWidgetAlpha_290770(o, id) <= 0.0f) {
                    UiSetWidgetsVisibleById_291110(o, id, 0, 1);
                    cnt++;
                }
                {
                    u16 id5m = (u16)id5;
                    UiMoveWidgetUniform_290f50(o, id5m, -0xA0, y, 26.0f, 1);
                    if (UiGetWidgetAlpha_290770(o, id5m) <= 0.0f) {
                        UiSetWidgetsVisibleById_291110(o, id5m, 0, 1);
                        cnt++;
                    }
                }
                {
                    u16 id10m = (u16)id10;
                    UiMoveWidgetUniform_290f50(o, id10m, -0xA0, y, 24.0f, 1);
                    if (UiGetWidgetAlpha_290770(o, id10m) <= 0.0f) {
                        UiSetWidgetsVisibleById_291110(o, id10m, 0, 1);
                        cnt++;
                    }
                }
            } else {
                if (o->f47C[i] > 0xF) {
                    UiFadeWidgetAlpha_290690(o, id, 0.0f, D_0047DA80, -1.0f);
                    UiFadeWidgetAlpha_290690(o, id5, 0.0f, D_0047DA84, -1.0f);
                    UiFadeWidgetAlpha_290690(o, id10, 0.0f, D_0047DA88, -1.0f);
                    *c = *c + 1;
                } else {
                    *c = o->f47C[i] + 1;
                }
            }
        }
        id++;
    }
    if (cnt == o->f47A * 3) {
        o->f382 = 0;
    }
}
