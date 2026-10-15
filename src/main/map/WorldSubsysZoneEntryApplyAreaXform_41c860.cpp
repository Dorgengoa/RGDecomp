#include "types.h"
#pragma opt_propagation off
#pragma opt_loop_invariants off

class VObj {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25();
    virtual s32 conv(s16);
};

extern "C" {
extern s32 GetMapMgr_201a90(void);
extern void *GetGameData_1fede0(void);
extern u8 *MapFindAreaSlotById_1e4cb0(s32, s32);
extern void MapDataGetPosVec4_1e7740(u8 *, void *);
extern void MapDataGetRotVec4_1e7720(u8 *, void *);
extern void MatFromRotPos_1caf90(void *, void *, void *);
extern void VecCopy_1cbe30(void *, void *);
extern void MatMulPoint_1cb8e0(void *, void *, void *);
extern f32 MapLinkedAreaGetYMaybe_3f09a0(u8 *, u8 *);
extern void IterInit_370170(void *, u8 *);
extern u8 *IterNext_370040(void *);
extern f32 D_00480240;
extern f32 D_00480244;
extern f32 D_00480248;
extern f32 D_0048024C;
extern f32 D_00480250;
extern f32 D_00480254;
extern f32 D_00480258;
extern f32 D_0048025C;
}

extern "C" s32 WorldSubsysZoneEntryApplyAreaXform_41c860(u8 *arg0, u8 *arg1) {
    s32 it[2];
    u8 v0[16];
    u8 v1[16];
    u8 m[64];
    u8 z[16];
    f32 b[4];
    f32 a[4];
    s32 g;
    u8 *e;
    s32 flag;
    s16 idx;
    f32 f;
    u8 *q;
    u8 *base;

    if (arg1 == 0) {
        return 0;
    }
    if (*(u8 **)(arg0 + 0x94) == 0) {
        return 0;
    }
    if (**(s32 **)(arg0 + 0x94) == 0) {
        return 0;
    }
    g = GetMapMgr_201a90();
    GetGameData_1fede0();
    e = 0;
    idx = *(s16 *)(*(u8 **)(arg0 + 0x94) + 8);
    flag = *(u8 *)(*(u8 **)(arg0 + 0x94) + 0xA) & 1;
    if (g != 0 && idx >= 0) {
        e = MapFindAreaSlotById_1e4cb0(g, idx);
    }
    if (e != 0 && flag != 0) {
        MapDataGetPosVec4_1e7740(e, v0);
        MapDataGetRotVec4_1e7720(e, v1);
        MatFromRotPos_1caf90(m, v1, v0);
    } else {
        s32 i;
        u8 *p = z;
        u32 n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        VecCopy_1cbe30(v0, z);
        VecCopy_1cbe30(v1, z);
        i = 0;
        do {
            VecCopy_1cbe30(m + i * 16, z);
            i++;
        } while (i < 4);
    }
    f = MapLinkedAreaGetYMaybe_3f09a0(arg1, *(u8 **)(arg0 + 0x94));
    base = arg0;
    if (arg0 != 0) {
        base = arg0 + 0x88;
    }
    IterInit_370170(it, base);
    while ((q = IterNext_370040(it)) != 0) {
        *(s32 *)(q + 0xC) = (*(VObj **)(*(u8 **)(arg1 + 0x6C) + 8))->conv(*(s16 *)(q + 0xC));
        *(u8 **)(q + 0x28) = *(u8 **)(arg0 + 0x94);
        if (flag != 0) {
            b[0] = D_00480240;
            b[1] = D_00480244;
            b[2] = D_00480248;
            b[3] = D_0048024C;
            b[0] = *(f32 *)(q + 0x38);
            b[1] = *(f32 *)(q + 0x3C);
            { f32 d = *(f32 *)(q + 0x40);
            a[0] = D_00480250;
            a[1] = D_00480254;
            a[2] = D_00480258;
            b[2] = d;
            a[3] = D_0048025C; }
            { f32 *p = b; MatMulPoint_1cb8e0(a, m, p); }
            *(f32 *)(q + 0x38) = a[0];
            *(f32 *)(q + 0x3C) = a[1];
            *(f32 *)(q + 0x40) = a[2];
        }
        if (f != 0.0f) {
            *(f32 *)(q + 0x3C) = *(f32 *)(q + 0x3C) + f;
        }
    }
    return 1;
}
