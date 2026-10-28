/* rgp:protos */
#define RGP_SELF_normal_FieldHudPartyPanelLayoutMaybe_4f7700 1
#include "port/game_protos.h"
#line 1
/* === LANE b1, NORMAL session 31.  PARKED at NINE bad words, LENGTH RIGHT
 * (181 words).  6 scoring round trips, 4 arms.  Baseline on disk was 14 bad.
 *
 * WHAT PAID (14 -> 9): the ten `v[i].x` stack stores are emitted by mwcc in
 * CONSTANT groups, and WITHIN a group in source order.  Retail's within-group
 * order is the REVERSE of the plain ascending source: 0xC4 before 0x94 (50.0f),
 * 0xB8 before 0x88 (130.0f), 0xDC before 0xD0 (0.0f).  A CHAINED ASSIGNMENT
 * spells that: `v[2].x = v[6].x = 130.0f;` stores the RIGHT-hand target first.
 * (Verified independently on normal_LeaderHudBannerLayout_506370, which CLOSED on the same
 * idiom for its sh store order.)
 *
 * RESIDUE -- ONE instruction out of place, everything else is the shift it
 * causes.  `sw $0,0xD0($29)` (v[8].x) belongs at 0x004F77CC, right after
 * `sw $0,0xDC`; ours sinks it 10 slots into the `jal func_2907A0` delay slot,
 * and retail's delay slot holds `sh $2,0x6($6)` instead.  Whichever store is
 * emitted LAST by the pre-scheduler wins the delay slot, and the second store
 * of the final chained zero pair is always it.
 *
 * MEASURED ARMS, 4:
 *   - reverse the within-group order by hand (explicit v6/v7/v2/v3/v9/v8
 *     statement order): 14 -> 9.  PAID 5.
 *   - chained assignment for all five pairs: byte-INERT vs the explicit
 *     reordering (identical object).  Kept -- it is the retail idiom.
 *   - move the 130.0f/50.0f statements AFTER the three zero statements, so the
 *     zero pair is not the block's last statement: 9 -> 22, WORSE.  The `lui`
 *     MATERIALISATION order follows source STATEMENT order, so $2/$3 swap
 *     (0x4F7774/0x4F777C go bad) and every store address goes with them.  The
 *     130/50 statements MUST precede the trailing zeros.
 *   - split the last chained cell store `c->a.h = c->b.h = (s16)v[3].x;` into
 *     two statements so `sh 0x6` is textually last: byte-INERT, still 9.
 *
 * NOT YET TRIED (for the next lane): declaring the last two cells as a
 * SEPARATE object (`V3 v[8]; V3 tail[2];`) so the 0xD0/0xDC stores are not
 * aliases of the same array, and giving v[8].x a value with a real dependence
 * instead of a folded 0. */
#include "types.h"
/* normal 0x004F7700 -- builds three widget-layout tables through the
 * func_290460 slot allocator.  184 instructions, frame -0xF0, six callee-saved
 * q-registers.
 *
 * The 120-byte stack block at $29+0x70 is TEN 12-byte objects with only the
 * first word of each written (0,0,130.0f,50.0f,0,0,130.0f,50.0f,0,0) -- mwcc
 * const-folds the loads, so only three `cvt.w.s` survive for the eight
 * (s16)float stores of the first cell.
 *
 * The record is a pair of s16 rectangles inside a 0x20-byte cell: retail's
 * store order groups equal constants (0xC before 0x4, 0xE before 0x6) in every
 * one of the three blocks, which is what a plain x/y/w/h source order gives
 * after mwcc reuses the materialised constant. */

typedef struct Rect { s16 x; s16 y; s16 w; s16 h; } Rect;
typedef struct Cell { Rect a; Rect b; u8 pad10[0x10]; } Cell;
typedef struct Slot { u8 pad00[0x20]; Cell *f20; } Slot;
typedef struct V3   { f32 x; f32 y; f32 z; } V3;

/*rgp*/
/*rgp*/
/*rgp*/


s32 normal_FieldHudPartyPanelLayoutMaybe_4f7700(s32 a0, s32 id, s32 a2, s32 a3)
{
    V3    v[10] __attribute__((aligned(16)));
    void *w;
    Slot *s;
    Cell *c;
    s32   n;
    s32   n1;
    s32   i;
    s32   j;

    w = normal_IdentityPtr_4f54d0((void *)a0);
    if (w == 0) {
        return 0;
    }
    n = id & 0xFFFF;
    n1 = (n + 1) & 0xFFFF;
    s = ((Slot *)UiFindWidget_290460(w, n1));
    if (s == 0) {
        return 0;
    }
    c = s->f20;
    if (c == 0) {
        return 0;
    }

    v[1].x = v[0].x = 0.0f;
    v[2].x = v[6].x = 130.0f;
    v[3].x = v[7].x = 50.0f;
    v[5].x = v[4].x = 0.0f;
    v[8].x = v[9].x = 0.0f;

    c->a.x = (s16)v[0].x;
    c->a.y = (s16)v[1].x;
    c->b.x = (s16)v[4].x;
    c->b.y = (s16)v[5].x;
    c->a.w = c->b.w = (s16)v[2].x;
    c->a.h = c->b.h = (s16)v[3].x;

    UiSetWidgetAlpha_2907a0(w, n1, 0.6999999881f);

    s = ((Slot *)UiFindWidget_290460(w, (n + 2) & 0xFFFF));
    if (s == 0) {
        return 0;
    }
    c = s->f20;
    if (c == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        c->a.x = 0x2A - i * 8;
        c->a.y = i * 21 + 0x14;
        c->b.x = 0;
        c->b.y = 0x32;
        c->a.w = c->b.w = 0x4E;
        c->a.h = c->b.h = 8;
        c++;
    }

    UiSetWidgetAlpha_2907a0(w, id, 0.6000000238f);

    s = ((Slot *)UiFindWidget_290460(w, (n + 3) & 0xFFFF));
    if (s == 0) {
        return 0;
    }
    c = s->f20;
    if (c == 0) {
        return 0;
    }
    for (j = 0; j < 2; j++) {
        c[0].a.x = 0x2E - j * 8;
        c[0].a.y = j * 21 + 7;
        c[0].b.x = 0xEC - j * 20;
        c[0].b.y = 0xC4;
        c[0].a.w = c[0].b.w = 0x14;
        c[0].a.h = c[0].b.h = 0xE;
        c[1].a.x = 0x2B - j * 8;
        c[1].a.y = j * 21 + 0x14;
        c[1].b.x = 0x86;
        c[1].b.y = j * 6;
        c[1].a.w = c[1].b.w = 0x4C;
        c[1].a.h = c[1].b.h = 6;
        c[2].a.x = 0x5D - j * 8;
        c[2].a.y = j * 21 + 8;
        c[2].b.x = 0x64;
        c[2].b.y = 0x62;
        c[2].a.w = c[2].b.w = 8;
        c[2].a.h = c[2].b.h = 0xC;
        c += 3;
    }
    return 1;
}
