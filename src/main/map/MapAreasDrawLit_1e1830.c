#include "types.h"
#include "vec.h"

typedef struct {
    s32 id;
    s32 z;
} Sel1e1830;

typedef struct {
    s32 id;
    s32 z;
    u8 pad8[8];
    Vec4 v00;
    Vec4 m[8];
    u8 pad90[0x20];
    Vec4 vB0;
    Vec4 vC0;
    u8 padD0[0x190 - 0xD0];
} Big1e1830;

typedef struct {
    u8 pad0[0x30];
    Vec4 m[8];
    u8 padB0[0x180 - 0xB0];
    Vec4 v180;
    Vec4 v190;
} Src1e1830;

extern void DrawListSortBuckets_140890(s32);
extern void LightStateSetCurrent_142920(s32, s32);
extern void LightStateEmitOnce_142950(s32);
extern s32 LightStatePush_1429f0(s32, s32 *, s32);
extern void LightStateInit_156b50(s32 *);
extern s32 GetDrawCtx_15de80(void);
extern Src1e1830 *MapGetAreaLightSetById_1e54d0(void *, s32, s32);
extern void MapDataDraw_1e63b0(s32, s32);
extern s32 MapDataGetDefaultLightSet_1e7b60(s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern void *GetCurrentScene_1f5be0(void);
extern f32 D_0047E3D0;
extern f32 D_0047E3D4;
extern f32 D_0047E3D8;
extern f32 D_0047E3DC;
extern f32 D_0047E3E0;
extern f32 D_0047E3E4;
extern f32 D_0047E3E8;
extern f32 D_0047E3EC;
extern f32 D_0047E3F0;
extern f32 D_0047E3F4;
extern f32 D_0047E3F8;
extern f32 D_0047E3FC;
extern f32 D_0047E400;
extern f32 D_0047E404;
extern f32 D_0047E408;
extern f32 D_0047E40C;
extern f32 D_0047E410;
extern f32 D_0047E414;
extern f32 D_0047E418;
extern f32 D_0047E41C;

void MapAreasDrawLit_1e1830(void *arg0, s32 arg1, s32 *arg2, s32 arg3)
{
    Big1e1830 big;
    Vec4 d;
    Vec4 c;
    Vec4 b;
    Vec4 a;
    Vec4 e;
    s32 ctx;
    s32 i;
    s32 r;
    s32 k0;
    Src1e1830 *src;
    Big1e1830 *pb;

    if (arg2 == 0 || arg3 < 1) {
        return;
    }
    pb = &big;
    GetCurrentScene_1f5be0();
    ctx = GetDrawCtx_15de80();
    big.z = 0;
    big.id = -1;
    LightStateInit_156b50(&big.id);
    LightStateInit_156b50(&big.id);
    i = 0;
    { f32 *p = (f32 *)&d; p[0] = D_0047E3D0; p[1] = D_0047E3D4; p[2] = D_0047E3D8; p[3] = D_0047E3DC; }
    { f32 *p = (f32 *)&c; p[0] = D_0047E3E0; p[1] = D_0047E3E4; p[2] = D_0047E3E8; p[3] = D_0047E3EC; }
    pb->m[0] = d;
    pb->m[0].w = 0;
    { f32 *p = (f32 *)&b; p[0] = D_0047E3F0; p[1] = D_0047E3F4; p[2] = D_0047E3F8; p[3] = D_0047E3FC; }
    pb->m[4] = c;
    { f32 *p = (f32 *)&a; p[0] = D_0047E400; p[1] = D_0047E404; p[2] = D_0047E408; p[3] = D_0047E40C; }
    pb->v00 = b;
    { f32 *p = (f32 *)&e; p[0] = D_0047E410; p[1] = D_0047E414; p[2] = D_0047E418; p[3] = D_0047E41C; }
    pb->vC0 = a;
    pb->vB0 = e;
    for (; i < arg3; i++, arg2++) {
        r = LightStatePush_1429f0(ctx, &big.id, 1);
        k0 = MapDataGetId_1e7bd0(*arg2);
        src = MapGetAreaLightSetById_1e54d0(arg0, k0, MapDataGetDefaultLightSet_1e7b60(*arg2));
        if (src != 0) {
            pb->m[0] = src->m[0];
            pb->m[1] = src->m[1];
            pb->m[2] = src->m[2];
            pb->m[3] = src->m[3];
            pb->m[4] = src->m[4];
            pb->m[5] = src->m[5];
            pb->m[6] = src->m[6];
            pb->m[7] = src->m[7];
            pb->v00 = src->v180;
            pb->vC0 = src->v190;
            pb->vB0 = e;
        }
        MapDataDraw_1e63b0(*arg2, arg1);
        LightStateSetCurrent_142920(ctx, r);
        LightStateEmitOnce_142950(ctx);
    }
    DrawListSortBuckets_140890(ctx);
}
