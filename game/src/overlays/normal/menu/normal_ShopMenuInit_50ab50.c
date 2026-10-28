/* rgp:protos */
#define RGP_SELF_normal_ShopMenuInit_50ab50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050AB50 -- the sibling of normal_ThinkMenuInit_5212b0: a 73-instruction,
 * ZERO-conditional-branch scene builder, 20 calls.  Same conventions: every
 * store written before a call fills that call's delay slot, allocator results
 * that are used immediately are locals, and everything read after an
 * intervening call is re-read from its global.
 * ⚠ `func_2A5920`'s prototype puts its two float parameters BEFORE the two
 * trailing integers.  Same registers either way -- the EABI numbers float and
 * integer arguments independently -- but the declaration order reaches the
 * SCHEDULE, and with the integers first mwcc fills the `mtc1`'s hazard slot
 * with `addiu $7,$0,1` and the unit is one word short.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern void *D_004845A8;
extern void *D_004845AC;
extern void *D_004845B0;
extern s16   D_004845B8;
extern void *D_004845C4;
extern void *D_004845C8;
extern void *D_004845CC;
extern void *D_004845D0;
extern void *D_004845D4;
extern u8    D_004845D8;
extern u8    D_004845DC;
extern s16   D_004845E0;
extern s16   D_004845E4;
extern void *D_004845FC;
extern s16   D_00480638;

extern u8  normal_D_00527C40;
extern u8  normal_D_00527C60;
extern u8  normal_D_00527C80;
extern s32 D_004659E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_ShopMenuInit_50ab50(void)
{
    void *h;

    D_004845A8 = SceneSoundGetSlot0HandleCur_207df0();
    D_004845E4 = 0;
    h = GetMenuTransdataStack_206a60();
    D_004845AC = h;
    MemStackReset_14d830(h);
    h = GetMenuTranstempStack_206a50();
    D_004845B0 = h;
    MemStackReset_14d830(h);
    normal_ShopMenuClutBufAlloc_50b120();
    D_004845DC = 0;
    D_004845E0 = 1;
    D_004845D8 = 1;
    D_00480638 = 1;
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    D_004845FC = 0;
    normal_ShopMenuResRequest_50b020();
    WorldDataRequestKind_3f0960(GetWorldDataMgr_1fedf0(), 8);
    normal_ShopMenuResPoll_50ae40();
    h = MemStackNew_14e230(0x1B4, D_004845AC);
    D_004845D4 = h;
    MenuItemGridInitMaybe_2a5920(h, (s8)(D_004659E8 + 1), 0, 1);
    MenuSetPanelHandles_2a5900(D_004845D4, &normal_D_00527C40, &normal_D_00527C80, &D_004845B8, D_004845AC);
    D_004845C4 = &D_004845B8;
    D_004845C8 = (void *)&normal_D_00527C40;
    D_004845D0 = (void *)&normal_D_00527C80;
    D_004845CC = (void *)&normal_D_00527C60;
}
