/* rgp:protos */
#define RGP_SELF_EventCastSetPosition_258a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } V4;
typedef union { u128 q; V4 v; } Vec;

typedef struct {
    s32 type;
    s32 id;
    s32 w8;
    void *obj;
} Ent;

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
extern V4 D_0047E8C0 __attribute__((section(".sdata")));

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

s32 EventCastSetPosition_258a50(Ent *tbl, s32 idx, f32 x, f32 y, f32 z) {
    Vec pos __attribute__((aligned(16)));
    u8 buf[0x6000] __attribute__((aligned(16)));
    Vec spE0 __attribute__((aligned(16)));
    Vec spD0 __attribute__((aligned(16)));
    Vec spC0 __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Vec)]; char m1[0x10 + sizeof(Vec)]; char m2[0x10]; char m3[0x20]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Vec) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    V4 sp90 __attribute__((aligned(16)));
    V4 sp80 __attribute__((aligned(16)));
    V4 sp70 __attribute__((aligned(16)));
    V4 sp60 __attribute__((aligned(16)));
    V4 sp50 __attribute__((aligned(16)));
    Ent *e;
    f32 r;
    void *o;
    s32 off;
    void *ob;
    void **pobj;
    s32 *pid;

    if (idx < 0 || idx >= 0x20) {
        return 0;
    }
    off = idx << 4;
    e = &tbl[idx];
    switch (e->type) {
    case 0:
        pos.v.w = 1.0f;
        pobj = &e->obj;
        pos.v.x = x;
        pos.v.y = y;
        pos.v.z = z;
        if (e->obj == 0) {
            return 0;
        }
        if (ObjRecGetFlags_1c3d90(GetCurrentScene_1f5be0(), 1, *(pid = &((Ent *)((s32)off + (s32)tbl))->id)) & 0x8000) {
            spE0.q = pos.q;
            spD0.q = pos.q;
            spE0.v.y += 1.0f;
            spD0.v.y -= 10.0f;
            r = VecDistance_13d3d0(&spE0, &spD0);
            VecMinMax_1cb570(&(*(Vec *)(rgp_blk1 + 0x0)), &(*(Vec *)(rgp_blk1 + 0x10)), &spE0, &spD0);
            (*(Vec *)(rgp_blk1 + 0x10)).v.w = 1.0f;
            (*(Vec *)(rgp_blk1 + 0x0)).v.w = 1.0f;
            (*(Vec *)(rgp_blk1 + 0x10)).v.x -= r;
            (*(Vec *)(rgp_blk1 + 0x10)).v.y -= r;
            (*(Vec *)(rgp_blk1 + 0x10)).v.z -= r;
            (*(Vec *)(rgp_blk1 + 0x0)).v.x += r;
            (*(Vec *)(rgp_blk1 + 0x0)).v.y += r;
            (*(Vec *)(rgp_blk1 + 0x0)).v.z += r;
            if (MeshRaycastWrapper_16f610(buf, MapEvCollectCollPolysMaybe_1ff270(buf, 0x100, &(*(Vec *)(rgp_blk1 + 0x0)), -1), &spE0, &spD0, &spC0, 1, 0) >= 0) {
                pos.q = spC0.q;
            }
            x = pos.v.x;
            y = pos.v.y;
            z = pos.v.z;
        }
        ob = *pobj;
        sp60 = D_0047E8C0;
        sp60.x = x;
        sp60.y = y;
        sp60.z = z;
        ModelSetPos_151110(ob, &sp60);
        o = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *pid);
        if (o != 0) {
            CharaSetPosXYZ_2139e0(o, x, y, z);
        }
        return 1;
    case 1:
        if (e->w8 != 0) { x = x; }
        o = ((Ent *)((s32)off + (s32)tbl))->obj;
        if (o == 0) {
            return 0;
        }
        BZERO(&sp50, 16);
        sp50.x = x;
        sp50.y = y;
        sp50.z = z;
        NodeSetTranslation_1866b0(o, &sp50);
        return 1;
    case 2:
        pobj = &e->obj;
        sp90.x = x;
        sp90.w = 1.0f;
        sp90.y = y;
        sp90.z = z;
        if (e->obj == 0) {
            return 0;
        }
        if (MenuWinGetDrawMode_26c290(e->obj) == 0) {
            MenuWinSetPos_26c3b0(*pobj, &sp90);
        } else if (MenuWinGetDrawMode_26c290(*pobj) == 1) {
            MenuWinSetPos_26c3b0(*pobj, &sp90);
        }
        return 1;
    case 3:
        sp80.x = x;
        sp80.w = 1.0f;
        sp80.y = y;
        sp80.z = z;
        if (e->obj == 0) {
            return 0;
        }
        FrameSetPos_14a450(e->obj, &sp80);
        return 1;
    case 4:
        if (e->w8 != 0) {
            sp70.x = x;
            sp70.w = 1.0f;
            sp70.y = y;
            sp70.z = z;
            if (e->obj == 0) {
                return 0;
            }
            NodeSetTranslation_1866b0(e->obj, &sp70);
        }
        return 1;
    }
    return 0;
}
