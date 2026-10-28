/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuItemGridLayout_5000b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* SESSION 41 (n41B, SOLO): CLOSED -- LENGTH-WRONG (0x23C vs 0x240) -> BYTE-
 * IDENTICAL at 144 words.  THREE edits, and no two of them are enough:
 *
 * 1. `#pragma opt_dead_assignments off` -- this is what fixes the LENGTH.  It
 *    was found by a whole-board pragma sweep (build/wf-normal/s41/pragboard.py),
 *    not by reading this unit: the same sweep moved `normal_MenuBattleEndItemRowsSlide_4eb4b0` from
 *    length-wrong to right-length as well.  ARMED: a bogus pragma name
 *    reproduces the length-wrong object exactly.
 * 2. `#pragma opt_pulloutconstants off` -- 6 bad -> 2.  Retail materialises the
 *    `1.0f`/`-1.0f` argument pair of the FIRST `func_2905B0` call into $3/$2;
 *    with the constant-pull on, mwcc creates the 1.0f web first and gets
 *    $2/$3, the mirror image.  (The SECOND call site was already right, which
 *    is what made the pair legible.)  Same lever as normal_FieldHudPartyPanelsRefresh_4f7d00's.
 * 3. `if (e->f08 > 1)` in place of `if (e->f08 >= 2)` -- the last 2 words.
 *    Both spellings emit `slti .., $7, 0x2`, but `>= 2` lets mwcc COALESCE the
 *    compare's result onto $7, the register the `lw` just loaded and which is
 *    dead after it, while `> 1` allocates a fresh temp -- and the pool is
 *    exhausted at that point, so the fresh temp is `$at`, exactly retail's
 *    `slti $1, $7, 0x2`.  ⚠ `> 1` is the ONLY spelling that does it: `>= 2`,
 *    `2 <= e->f08`, `!(e->f08 < 2)`, reading through `*np` or `np[0]`, and a
 *    named `s32 f08` temp all leave it at 2 bad; `np` assigned after the guard
 *    is length-wrong again, and reusing the temp in the body is 19.
 *    ⇒ NEW LEVER: on an exhausted caller-saved pool the COMPARE SPELLING picks
 *    the temp -- `>= K` coalesces onto the compared register, `> K-1` does not.
 */
#pragma opt_dead_assignments off
#pragma opt_pulloutconstants off
/* normal 0x005000B0 -- session 31 lane n31c, FRESH.
 * Refreshes the two 0x21-entry quest-board widget rows (func_28FE10 id 0x26
 * = the icon row, func_28F2B0 id 0x27 = the count row) from the normal_D_00527910
 * slot table normal_FUN_005002F0 rebuilds.  Slot.f04 is a linear index that
 * is split into a 44-wide column and a 50-tall row; Slot.f0C is a second
 * index split into a 32x32 cell.  Empty slots (f00 == -1) blank both rows.
 *
 * `sd` into Num.f08 is a 64-bit member ([[normal_BtlChgPageRowTextLayout_505a50]] /
 * [[normal_FieldHudAttackChainOpen_4f6bf0]]); the hoisted `dsll32/dsra32 ,16` in the loop
 * preheader is an s16 member read BACK OUT of the register its own store
 * used (the tell recorded in normal_FUN_005002F0's header), which is why the
 * blank paths are spelled `pb[i].f08 = pb[i].f1C;` and not `= 0`.
 * The second reads of Slot.f0C and Slot.f08 go through `&e->member`
 * ([[mwcc-member-address-no-cse]]) because retail materialises $11+0xC and
 * $11+0x8 into their own registers instead of re-using the base+offset. */

typedef struct Slot { s32 f00; s32 f04; s32 f08; s16 f0C; s16 f0E; } Slot;

typedef struct Row {
    s16 f00; s16 f02; s16 f04; s16 f06;
    s16 f08; s16 f0A; s16 f0C; s16 f0E;
    u8  pad10[0xC];
    u16 f1C;
    s16 f1E;
} Row;

typedef struct Num {
    s16 f00; s16 f02;
    u8  pad04[4];
    s64 f08;
    u8  pad10[0xC];
    s16 f1C;
    s16 f1E;
} Num;

extern Slot  normal_D_00527910[];
extern void *D_0048449C;          /* gp - 0xCD4 */

/*rgp*/
/*rgp*/
/*rgp*/

void normal_BtlChgMenuItemGridLayout_5000b0(void)
{
    Row  *pa;
    Num  *pb;
    s32   i;
    Slot *e;
    s32   v;
    s32   r;
    s32   q;
    s16  *cp;
    s32  *np;

    pa = ((Row *)UiGetWidgetSprite_28fe10(D_0048449C, 0x26, 0));
    if (pa != 0) {
        pb = ((Num *)UiGetWidgetSubItem_28f2b0(D_0048449C, 0x27, 0));
        if (pb != 0) {
            UiSetWidgetColor_2905b0(D_0048449C, 0x26, 1.0f, 1.0f, 1.0f, -1.0f);
            UiSetWidgetColor_2905b0(D_0048449C, 0x27, 1.0f, 1.0f, 1.0f, -1.0f);
            for (i = 0; i < 0x21; i++) {
                e = &normal_D_00527910[i];
                if (e->f00 == -1) {
                    pa[i].f0E = 0;
                    pa[i].f0C = 0;
                    pa[i].f06 = 0;
                    pa[i].f04 = 0;
                    pb[i].f1E = 0;
                    pb[i].f1C = 0;
                    pb[i].f08 = pb[i].f1C;
                } else {
                    v = e->f04;
                    r = v % 8;
                    q = v / 8;
                    pa[i].f00 = (s16)(r * 44 + 2);
                    pa[i].f02 = (s16)(q * 50 - 1);
                    pa[i].f04 = 0x28;
                    pa[i].f06 = 0x2D;
                    pa[i].f0C = 0x20;
                    pa[i].f0E = 0x20;
                    cp = &e->f0C;
                    pa[i].f08 = (s16)(*cp % 8 * 32);
                    pa[i].f0A = (s16)(*cp / 8 * 32);
                    pa[i].f1C |= 2;
                    np = &e->f08;
                    if (e->f08 > 1) {
                        pb[(u32)i].f00 = (s16)(r * 44 + 2);
                        pb[(u32)i].f02 = (s16)(q * 50 - 1);
                        pb[(u32)i].f08 = *np;
                        pb[(u32)i].f1C = 0xA;
                        pb[(u32)i].f1E = 0x10;
                    } else {
                        pb[(u32)i].f1E = 0;
                        pb[(u32)i].f1C = 0;
                        pb[(u32)i].f08 = pb[(u32)i].f1C;
                    }
                }
            }
            pa[0x21].f00 = -1;
            pb[0x21].f00 = -1;
        }
    }
}
