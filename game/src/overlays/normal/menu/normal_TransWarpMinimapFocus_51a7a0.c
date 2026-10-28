/* rgp:protos */
#define RGP_SELF_normal_TransWarpMinimapFocus_51a7a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s16   f00;
    s32   f04;
    s32   f08;
    s32   f0C;
    s32   f10;
    void *f14;
    s8    f18;
    u8    pad19[7];
    f32   f20;
    f32   f24;
    f32   f28;
    s32   f2C;
} Ent;

typedef struct Wk {
    u8  pad00[0x12];
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Wk;

typedef struct Pl {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Pl;

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

extern f32   D_0047D9DC;   /* gp - 0x7794 */
extern void *D_00484710;   /* gp - 0xA60  */
extern void *D_00484848;   /* gp - 0x928  */
extern Ent  *D_00484870;   /* gp - 0x900  */

extern void *strcmp(void *p, void *q);
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

void normal_TransWarpMinimapFocus_51a7a0(Wk *a)
{
    s32   n;
    Vec   v __attribute__((aligned(16)));
    Pl   *pl;
    void *p2;
    void *r;
    void *h;
    void *o;
    s32   i;

    if (a != 0) {
        GetGameData_1fede0();
        i = a->f12 + a->f16;
        if (D_00484870[i].f00 == 3) {
            pl = ((Pl *)GetMinimapMgr_201a70());
            if (pl != 0) {
                h = D_00484870[i].f14;
                p2 = GetMapMgr_201a90();
                if (p2 != 0) {
                    n = 0;
                    r = MapSlotsFindBlockById_1e49b0(p2, h, &n);
                    if (n != 0) {
                        MinimapMgrTrackActiveSlot_321ea0(pl, MapDataGetName_1e7bf0(n));
                        h = pl->f514;
                        if (h == 0) {
                            h = pl->f510;
                        }
                        if (r != 0) {
                            MinimapSelectEntryByName_324a70(h, MapBlockGetOwnName_1dfef0(r), &D_00484870[i].f20);
                            MapDataGetPosVec4_1e7740(MapSlotsFindBlockByName_1e4910(p2, MinimapGetEntryBlockName_324a40(h), 0), &v);
                            MinimapSetTargetPosMaybe_324bb0(h, &v);
                            if (D_00484848 != 0) {
                                o = MinimapGetPendingOrCurEntry_32a8f0(h);
                                if (o != 0) {
                                    if (strcmp(D_00484848, (void *)((u8 *)o + 0x54)) != 0) {
                                        UiFadeWidgetAlpha_290690(D_00484710, 0x75D1, 0.0f, D_0047D9DC, -1.0f);
                                    } else {
                                        UiFadeWidgetAlpha_290690(D_00484710, 0x75D1, 1.0f, D_0047D9DC, -1.0f);
                                        UiSetWidgetsVisibleById_291110(D_00484710, 0x75D1, 1, 1);
                                    }
                                }
                            }
                        }
                        if (h == pl->f510) {
                            MinimapFadeIn_329ef0(h, 15.0f);
                        }
                    }
                }
            }
        }
    }
}
