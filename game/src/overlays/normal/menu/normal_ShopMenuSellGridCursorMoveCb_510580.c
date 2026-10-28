/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellGridCursorMoveCb_510580 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510580 -- map/marker bring-up.
 * ⚠ D_004845D4 is a POINTER here (`lw` then `lb 0x11($3)`).  It is also
 * written as `sw $0` in normal_FUN_0050A630, where it is declared s32 -- the
 * two spellings produce the same word, so that unit is byte-identical either
 * way; this one is the site that names the type. */
typedef struct Obj { u8 pad000[0x10]; s16 f10; s16 f12; } Obj;
typedef struct Cfg { u8 pad00[0x11]; s8 f11; } Cfg;
typedef struct Ctx { u8 pad00[0x18]; void *f18; } Ctx;

extern u8 normal_D_00527E70[];
extern Cfg  *D_004845D4;
extern s32   D_00484680;
extern f32   D_0047D240;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellGridCursorMoveCb_510580(Obj *p)
{
    UiSelFrameSetGridCell_28db00(normal_D_00527E70, 0x3F, p->f10, p->f12, 0x50, 0x49);
    normal_ShopMenuItemInfoShow_509520(InvFindByCategoryIndex_3c86e0(((Ctx *)GetGameData_1fede0())->f18, 0, D_004845D4->f11,
                                    p->f10, p->f12, 0),
                        0x34, 0x33, 0x57, 0x15E, D_0047D240);
    D_00484680 = 0;
    normal_ShopMenuSellCellHintShow_50f650(0);
    return 1;
}
