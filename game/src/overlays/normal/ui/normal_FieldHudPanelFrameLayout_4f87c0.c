/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelFrameLayout_4f87c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F87C0 -- lays out the party-formation panel's three two-box
 * rows.  A constructor-shaped INITIALISER: three guards, one call for the
 * party count, then 24 constant halfword stores into a 0x20-stride row array.
 * Found by the main-side pass-33 LIST rank -- 228 bytes, 57 instructions,
 * THREE branches, 27 stores.
 *
 * normal_D_005261E0 is read through %hi/%lo, not %gp_rel, so it is overlay data and
 * takes the `const` incomplete-array declaration; the table is the four party
 * column origins 0, 0x84, 0x101, 0x17D.
 *
 * Each row is two {x,y,w,h} boxes: the caret box A and the label box B.  The
 * store ORDER is the source's -- mwcc does not reschedule these -- and it is
 * NOT address order: within a row it is A.x A.y B.x B.y then the two widths
 * and the two heights B-first, except in row 1 where the width that comes from
 * the table is written first.
 *
 * The COLUMN ORIGIN IS READ AT ITS USE, NOT INTO A NAMED LOCAL.  With
 * `v = normal_D_005261E0[k];` hoisted to its own statement the `lh` runs before the
 * store block, takes $7, and pushes the constant 8 into $6 -- 30 bad words at
 * the right length, every one of them a register.  Written inline at both uses
 * mwcc still emits ONE `lh` (same basic block, so it CSEs) but places it where
 * retail does, in the middle of row 1.  This is the exact mirror of
 * levers.d/normal-named-product-local: naming a value MOVES ITS COMPUTATION,
 * and which direction pays depends on where retail put it.
 */

typedef struct Box  { s16 x; s16 y; s16 w; s16 h; } Box;
typedef struct Row  { Box a; Box b; u8 pad10[0x10]; } Row;
typedef struct Hold { u8 pad000[0x20]; Row *f020; } Hold;

extern s16 normal_D_005261E0[];

/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_FieldHudPanelFrameLayout_4f87c0(void *p);

void normal_FieldHudPanelFrameLayout_4f87c0(void *p)
{
    Hold *h;
    Row  *r;
    s32   k;

    h = ((Hold *)UiFindWidget_290460(p, 2));
    if (h == 0) {
        return;
    }
    r = h->f020;
    if (r == 0) {
        return;
    }
    if (GetGameData_1fede0() == 0) {
        return;
    }
    k = normal_FieldHudPartyRowCount_4f9c50();

    r[0].a.x = 0;
    r[0].a.y = 0;
    r[0].b.x = 0xD2;
    r[0].b.y = 0;
    r[0].b.w = 8;
    r[0].a.w = 8;
    r[0].b.h = 8;
    r[0].a.h = 8;

    r[1].a.x = 8;
    r[1].a.y = 0;
    r[1].b.x = 0xD8;
    r[1].b.y = 0;
    r[1].a.w = normal_D_005261E0[k];
    r[1].b.w = 8;
    r[1].b.h = 8;
    r[1].a.h = 8;

    r[2].a.x = normal_D_005261E0[k] + 8;
    r[2].a.y = 0;
    r[2].b.x = 0xDE;
    r[2].b.y = 0;
    r[2].b.w = 8;
    r[2].a.w = 8;
    r[2].b.h = 8;
    r[2].a.h = 8;
}
