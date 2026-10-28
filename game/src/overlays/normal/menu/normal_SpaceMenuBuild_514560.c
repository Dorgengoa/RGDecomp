/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuBuild_514560 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00514560 -- the gameplay HUD/panel builder: one long call sequence
 * on a single object.
 *
 * `lhu 0xA / dsll32 16 / dsrl32 18` is a 14-BIT BITFIELD at bits 2..15 of the
 * halfword, and both it and `rec->f4` are read BEFORE the intervening
 * func_2912E0 call, so each needs its own local.
 * `p->f8 = 0x32D;` is written BEFORE func_290450(p) so the `sw` fills that
 * call's delay slot. */
typedef struct Rec {
    u8    pad00[4];
    void *f04;
    u8    pad08[2];
    __extension__ unsigned short   fA_lo : 2;
    unsigned short   fA_hi : 14;
} __attribute__((aligned(2))) Rec;

typedef struct Obj {
    u8  pad00[8];
    s32 f08;
    u8  pad0C[0x14 - 0x0C];
    s8  f14;
} Obj;

extern void *D_004846B0;
extern void *D_00481BBC;
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

s32 normal_SpaceMenuBuild_514560(Obj *p)
{
    Rec *r;
    void *t;
    s32 n;

    r = ((Rec *)ResGroupListFindById_42c500(GetMenuResGroup_206a40(), 0xE));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(p);
    UiInitWidgetPool_290390(p, D_004846B0, n);
    UiAddWidgets_2901d0(p, t, 0);
    p->f08 = 0x32D;
    UiTextStyleReset_290450();
    UiSetWidgetsVisibleById_291110(p, 2, 1, 1);
    UiSetWidgetPos_290f60(p, 2, 0, 0);
    UiSetWidgetsVisibleById_291110(p, 0x27, 1, 1);
    UiSetWidgetPos_290f60(p, 0x27, 0, 0);
    UiSetWidgetVisible_290010(p, 0x20, 1, -1);
    UiSetWidgetPos_290f60(p, 0x20, 0, 0);
    UiSetTextString_28f510(p, 0x21, MsgTableLookup_28aa30(D_00481BBC, 0x57), 0);
    normal_SpaceMenuPanelsLayout_514270(p);
    normal_SpaceMenuMapBuild_5135f0(p);
    normal_SpaceMenuSelectionRefresh_512a70(p);
    normal_SpaceMenuOpenAnimStart_512e20(p);
    p->f14 = 1;
    return 0;
}
