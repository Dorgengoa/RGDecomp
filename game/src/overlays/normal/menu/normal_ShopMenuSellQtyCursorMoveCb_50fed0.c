/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellQtyCursorMoveCb_50fed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050FED0 -- confirm handler: bumps or resets the row, resolves the
 * page record, runs the six-argument probe and only then commits.  The
 * func_291250's fourth argument here is o->f10, s32 (not the s64 value slot
 * the 0x0050BB00 site uses) -- the dead `lh $7` in the bnel delay slot is it. */
typedef struct Obj  { u8 pad00[0x10]; s16 f10; } Obj;
typedef struct Page { u8 pad00[0x14]; s16 f14; s16 f16; } Page;
typedef struct Cfg  { u8 pad00[0x11]; s8 f11; } Cfg;
typedef struct Sys  { u8 pad00[0x18]; void *f18; } Sys;

extern void *D_004845CC;              /* gp - 0xBA4 */
extern void *D_004845D0;              /* gp - 0xBA0 */
extern Cfg  *D_004845D4;              /* gp - 0xB9C */
extern void *D_0048467C;              /* gp - 0xAF4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellQtyCursorMoveCb_50fed0(Obj *o)
{
    Page *pg;

    if (o->f10 <= 0) {
        o->f10 = 1;
    } else {
        PlayMenuSe_289ef0(4);
    }
    pg = ((Page *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7534));
    if (((s32)InvFindByCategoryIndex_3c86e0(((Sys *)GetGameData_1fede0())->f18, 0, D_004845D4->f11, pg->f14, pg->f16, 0)) == 0) {
        return 0;
    }
    UiSetWidgetSubItemValue_291250(D_004845CC, 0x4F, 0, (long long)(o->f10));
    normal_ShopMenuSellTotalPriceSet_50ec80(((short)ItemGetSellPrice_3d4320(D_0048467C)), o->f10);
    return 1;
}
