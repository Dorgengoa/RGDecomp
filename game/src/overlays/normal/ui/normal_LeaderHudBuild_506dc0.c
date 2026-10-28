/* rgp:protos */
#define RGP_SELF_normal_LeaderHudBuild_506dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506DC0 -- build the 0x527C00 widget from the current record. */
/* the `dsll32 16 / dsrl32 18` off a plain `lhu` is an UNSIGNED BITFIELD of
 * width 14 at bit 2 of the u16 container at 0x0A -- not a shift of a u16. */
typedef struct Rec { u8 pad00[4]; s32 f04; u8 pad08[2];
                     __extension__ unsigned short pad0A : 2; unsigned short f0A : 14; } __attribute__((aligned(2))) Rec;
typedef struct Obj { u8 pad00[0x94]; s32 f94; u8 pad98[0xA6 - 0x98]; s16 fA6; } Obj;

extern u8 normal_D_00527C00[];
extern s32 normal_D_00527C08[];
extern u8 D_004BC250[];

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

extern s32 normal_LeaderHudBuild_506dc0(Obj *p, void *s);
s32 normal_LeaderHudBuild_506dc0(Obj *p, void *s)
{
    void *h;
    Rec *r;
    s32 v;
    s32 n;

    if (s != 0) {
        h = GetMenuResGroup_206a40();
        r = ((Rec *)ResGroupListFindById_42c500(h, 0x15));
        v = r->f04;
        n = r->f0A;
        UiWidgetListReset_2912e0(normal_D_00527C00);
        UiInitWidgetPool_290390(normal_D_00527C00, s, n);
        UiAddWidgets_2901d0(normal_D_00527C00, v, 0);
        normal_D_00527C08[0] = 0x32B;
        ResGroupListFindById_42c040(h, 0xA);
        normal_LeaderHudReset_506ef0(D_004BC250);
        UiPageSetMemStack_289c40(D_004BC250, s);
        UiPageSetStateTable_289c10(D_004BC250, MenuStateTableForId_42c950(h, 0xC));
        p->f94 = SceneSoundGetSlot0HandleCur_207df0();
        UiPageSetLayout_289c30(D_004BC250, normal_D_00527C00);
    }
    p->fA6 = 1;
    return 0;
}
