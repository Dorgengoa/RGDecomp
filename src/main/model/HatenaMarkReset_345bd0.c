#include "types.h"

typedef struct { f32 x, y, z, w; } V4;

typedef struct {
    s32 x0;
    u8 pad4[8];
    u8 xC;
    u8 xD;
    u8 padE[2];
    V4 v10;
    V4 v20;
    V4 v30;
    V4 v40;
    u8 pad50[0x10];
    V4 v60;
    V4 v70;
    V4 v80;
    f32 x90;
    s32 x94;
    s32 x98;
    f32 x9C;
    u8 xA0;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 pad : 4;
    s16 xA2;
    s32 xA4;
} O;

extern void sceVu0CopyVector(V4 *dst, V4 *src);
extern f32 D_0047F660[4] __attribute__((section(".sdata")));
extern f32 D_0047F670[4] __attribute__((section(".sdata")));
extern const f32 D_0047DADC __attribute__((section(".sdata")));

s32 HatenaMarkReset_345bd0(O *o)
{
    V4 a;
    V4 b;

    o->x0 = 0;
    o->xC = 0;
    o->xD = 0;
    { f32 *pa = (f32 *)&a; pa[0] = D_0047F660[0]; pa[1] = D_0047F660[1]; pa[2] = D_0047F660[2]; pa[3] = D_0047F660[3]; }
    { f32 *pb = (f32 *)&b; pb[0] = D_0047F670[0]; pb[1] = D_0047F670[1]; pb[2] = D_0047F670[2]; pb[3] = D_0047F670[3]; }
    sceVu0CopyVector(&o->v10, &a);
    sceVu0CopyVector(&o->v20, &a);
    sceVu0CopyVector(&o->v60, &a);
    sceVu0CopyVector(&o->v70, &b);
    sceVu0CopyVector(&o->v80, &b);
    sceVu0CopyVector(&o->v30, &a);
    sceVu0CopyVector(&o->v40, &a);
    o->x90 = 16.0f;
    o->x98 = 0;
    o->x94 = 0;
    o->f0 = 0;
    o->f1 = 1;
    o->f2 = 0;
    o->f3 = 0;
    o->x9C = D_0047DADC;
    o->xA2 = -1;
    o->xA4 = 0;
    o->xA0 = 1;
    return 0;
}
