/* rgp:protos */
#define RGP_SELF_normal_ShopMenuDiscountIconRefresh_50b140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050B140 -- picks which of the three 0x40FB..0x40FD shop lists the
 * player is standing at.  The u8 at gp-0xB30 is the 3/2/1 rank (0 = none);
 * with no list the three panels are just switched off. */

typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;
typedef struct Rec  { u8 pad00[0x2C]; s16 f2C; } Rec;
typedef struct Ent  { u8 pad00[0x10]; Rec *f10; } Ent;

extern void *D_004845C8;          /* gp - 0xBA8 */
extern volatile u8 D_00484640;          /* gp - 0xB30 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuDiscountIconRefresh_50b140(void)
{
    Root *root;
    s32   id;
    void *w;
    Ent  *e;
    Rec  *rc;

    root = ((Root *)GetGameData_1fede0());
    id = -1;
    if (InvHasItemInCategory_3c7f40(root->f18, 0x40FB, 0xA, 0) != 0) {
        D_00484640 = 3;
        id = 0x40FB;
    } else if (InvHasItemInCategory_3c7f40(root->f18, 0x40FC, 0xA, 0) != 0) {
        D_00484640 = 2;
        id = 0x40FC;
    } else if (InvHasItemInCategory_3c7f40(root->f18, 0x40FD, 0xA, 0) != 0) {
        D_00484640 = 1;
        id = 0x40FD;
    } else {
        D_00484640 = 0;
    }
    if (D_00484640 == 0) {
        UiSetWidgetsVisibleById_291110(D_004845C8, 0x1F, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004845C8, 0x1E, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004845C8, 0x26, 0, 1);
        return 1;
    }
    w = UiGetWidgetSprite_28fe10(D_004845C8, 0x26, 0);
    if (w == 0) {
        return 0;
    }
    e = ((Ent *)InvFindInCategoryRange_3c8370(root->f18, id, 0xA, -1, 0, 0));
    if (e == 0) {
        return 0;
    }
    rc = e->f10;
    UiSetItemIconUv_288e50(w, rc->f2C, 0x20, 0x20);
    return 1;
}
