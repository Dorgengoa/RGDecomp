/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuInit_5212b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005212B0 -- an 81-instruction, ZERO-conditional-branch scene
 * builder: 18 calls and 11 gp publishes.  Every value is re-read from its
 * global at each use because a call separates the uses (mwcc's per-basic-block
 * CSE reproduces that for free); the two allocator results that are used
 * immediately are held in locals instead.
 *
 * The overlay-data addresses (`normal_D_00528030`, `normal_D_00526050`, `normal_D_00528060`) and
 * the two main-image addresses are all `const` -- 0x00528030 is 0xA2EC0 past
 * `_gp`, so a `%gp_rel` relocation would not resolve and the LINK would fail
 * with a GP offset overflow while the object compiled clean.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern void *D_00484918;
extern void *D_0048491C;
extern void *D_00484920;
extern s16   D_00484928;
extern s32   D_0048492C;
extern void *D_00484930;
extern void *D_00484934;
extern u8    D_00484938;
extern u8    D_0048493C;
extern u8    D_00484940;
extern u8    D_00480788;

extern u8  normal_D_00526050;
extern u8  normal_D_00528030;
extern u8  normal_D_00528060;
extern u8  D_004B2570;
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
/*rgp*/
/*rgp*/

void normal_ThinkMenuInit_5212b0(void)
{
    void *h;

    D_00484940 = 0;
    h = GetMenuTransdataStack_206a60();
    D_00484918 = h;
    MemStackReset_14d830(h);
    h = GetMenuTranstempStack_206a50();
    D_0048491C = h;
    MemStackReset_14d830(h);
    h = MemStackNew_14e230(0x14, D_00484918);
    D_00484920 = h;
    UiWidgetListReset_2912e0(h);
    UiEntryListReset_28ec80(&normal_D_00528030);
    D_00484930 = (void *)&normal_D_00526050;
    D_0048492C = 0;
    D_00484928 = 0;
    PadClearRepeatAll_183960(&D_004B2570);
    PadSetRepeat_183d50(&D_004B2570, 0xF00C, 0xA, 3);
    PadSetStickDpadThreshold_183950(&D_004B2570, 0x78);
    D_0048493C = 1;
    D_00484938 = 1;
    D_00480788 = 1;
    UiSelFrameReset_28db70(&normal_D_00528060);
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    h = MemStackNew_14e230(0x1B4, D_00484918);
    D_00484934 = h;
    MenuItemGridInitMaybe_2a5920(h, (s8)(D_004659E8 + 1), 0, 1);
    MenuSetPanelHandles_2a5900(D_00484934, D_00484920, &normal_D_00528030, &D_00484928, D_00484918);
    normal_ThinkMenuResRequest_5218d0();
    normal_ThinkMenuResPoll_5217e0();
}
