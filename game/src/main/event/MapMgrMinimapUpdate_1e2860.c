/* rgp:protos */
#define RGP_SELF_MapMgrMinimapUpdate_1e2860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047E3B0;
extern f32 D_0047E3B4;
extern f32 D_0047E3B8;
extern f32 D_0047E3BC;
extern f32 D_0047E3C0;
extern f32 D_0047E3C4;
extern f32 D_0047E3C8;
extern f32 D_0047E3CC;
extern u8 D_004B2570[];

void MapMgrMinimapUpdate_1e2860(u8 *self, s32 arg1) {
    Vec4 v80 __attribute__((aligned(16)));
    Vec4 v70 __attribute__((aligned(16)));
    Vec4 v60 __attribute__((aligned(16)));
    u8 *p;
    s32 k;
    s32 r;
    s32 m;
    s32 e;
    u8 *d;
    s32 q;
    s32 h;
    s32 i;
    s32 c;
    Vec4 *pv;


    p = ((u8 *)GetMinimapMgr_201a70());
    k = 0;
    m = 0;
    e = MapSlotsFindBlockById_1e49b0(self, arg1, 0);
    if (e != 0) {
        k = MapBlockGetOwnName_1dfef0(e);
        r = ((s32)MapFindAreaSlotById_1e4cb0(self, ((short)MapDataGetParentId_1e7bb0(e))));
        if (r != 0) {
            m = MapDataGetName_1e7bf0(r);
        }
    }
    MinimapMgrTrackActiveSlot_321ea0(p, m);
    d = ((u8 *)GetGameData_1fede0());
    q = ((s32)GetActionMgr_1fdb50());
    GetMapMgr_201a90();
    v80.x = D_0047E3B0;
    v80.y = D_0047E3B4;
    v80.z = D_0047E3B8;
    v80.w = D_0047E3BC;
    h = ((s32)ActionMgrFindById_233b50(q, *(s16 *)(*(u8 **)(d + 0x18) + 0x18E)));
    if (h != 0) {
        CharaGetPos_2388a0(h, &v80);
    }
    if (*(s32 *)(self + 0x60) & 4) {
        *(f32 *)(self + 0x22A0) += 0.75f * (f32)PadGetAnalogLX_1840d0(D_004B2570);
        *(f32 *)(self + 0x22A8) += 0.75f * (f32)PadGetAnalogLY_184050(D_004B2570);
        VecAdd_1cbdc0(&v70, &v80, (f32 *)(self + 0x22A0));
        if (MinimapMgrMoveAllToPos_3217d0(p, &v70, 1, 0) == 0) {
            *(f32 *)(self + 0x22A0) = v70.x - v80.x;
            *(f32 *)(self + 0x22A8) = v70.z - v80.z;
        }
    }
    for (i = 0; i < 4; i++) {
        c = *(s32 *)(p + 0x514);
        if (c == 0) {
            c = *(s32 *)(p + 0x510);
        }
        if (c != 0) {
            MinimapSelectEntryByName_324a70(c, k, &v80);
            r = MapSlotsFindBlockByName_1e4910(self, MinimapGetEntryBlockName_324a40(c), 0);
            pv = &v60;
            v60.x = D_0047E3C0;
            v60.y = D_0047E3C4;
            v60.z = D_0047E3C8;
            v60.w = D_0047E3CC;
            if (r != 0) {
                MapDataGetPosVec4_1e7740(r, pv);
            }
            MinimapSetTargetPosMaybe_324bb0(c, &v60);
        }
    }
    MinimapMgrUpdate_322030(p, &v80);
}
