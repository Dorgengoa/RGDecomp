/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuItemListBuild_5002f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005002F0 -- rebuilds the 0x21-entry quest board.  The table at
 * normal_D_00527910 is reset to {-1, ?, 0, -1} and then re-filled, compacted, from
 * the 0x21 ids in normal_D_00525070 that func_3C8370 actually resolves; the surviving
 * count is turned into a page count (a signed `/ 8`, which is why retail has
 * the `bgez / addiu 7 / sra 3` bias) and handed to normal_FUN_005004B0.
 *
 * `n` starts at -1 and is PRE-incremented, so it is the last written index,
 * not a count; the `bgezl $20` after the loop is the `n < 0` clamp for the
 * "nothing resolved" case.  The `dsll32/dsra32 ..,16` is the s16 member being
 * read back out of the register the store used, not a reload.
 * `lw $2,0x10($17)` appears twice because both members are read AT THEIR USE. */

typedef struct Slot { s32 f00; s32 f04; s32 f08; s16 f0C; s16 f0E; } Slot;
typedef struct Info { s16 f00; u8 pad02[0x2E - 2]; s16 f2E; } Info;
typedef struct Obj  { u8 pad00[0x10]; Info *f10; } Obj;
typedef struct Rec  { u8 pad00[0x1C]; s16 f1C; u8 pad1E[2]; } Rec;
typedef struct Hdl  { u8 pad00[0xE]; s16 f0E; u8 pad10[2]; s16 f12; } Hdl;
typedef struct Root { u8 pad00[0x18]; void *f18; } Root;

extern u8 normal_D_00526430[];
extern s32   normal_D_00525070[];
extern Slot  normal_D_00527910[];

extern f32   D_004844B0;          /* gp - 0xCC0 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_004844A0;          /* gp - 0xCD0 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_BtlChgMenuItemListBuild_5002f0(void)
{
    Root *root;
    s32   n;
    Rec  *p;
    s32   i;
    Obj  *ob;
    Hdl  *h;
    s32   j;

    root = ((Root *)GetGameData_1fede0());
    if (root == 0) {
        return;
    }
    for (j = 0; j < 0x21; j++) {
        normal_D_00527910[j].f00 = -1;
        normal_D_00527910[j].f0C = -1;
        normal_D_00527910[j].f08 = 0;
    }
    UiSetWidgetTexName_290ac0(D_0048449C, 0x26, normal_D_00526430);
    n = -1;
    p = ((Rec *)UiGetWidgetSprite_28fe10(D_0048449C, 0x26, 0));
    if (p == 0) {
        return;
    }
    for (i = 0; i < 0x21; i++) {
        p->f1C = 0;
        ob = ((Obj *)InvFindInCategoryRange_3c8370(root->f18, normal_D_00525070[i], 0, -1, 0, 0));
        if (ob != 0) {
            n++;
            normal_D_00527910[n].f00 = normal_D_00525070[i];
            normal_D_00527910[n].f04 = n;
            normal_D_00527910[n].f0C = ob->f10->f2E;
            if (ItemHasCountFlag_3d44e0(ob) != 0) {
                normal_D_00527910[n].f08 = InvCountById_3c78d0(root->f18, ob->f10->f00, 0, 0);
            }
        }
        p++;
    }
    if (n < 0) {
        n = 0;
    }
    h = ((Hdl *)UiEntryListFindByTag_28ea40(D_004844A0, 0x55F3));
    h->f12 = (s16)(n / 8);
    D_004844B0 = normal_BtlChgMenuScrollBarLayout_5004b0(0x25, 0x5A, h->f0E + 1, h->f12 + 1, 0);
}
