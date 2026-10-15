#include "types.h"

typedef unsigned __int128 u128;

typedef union Vec4 {
    u128 q;
    f32 f[4];
    s32 i[4];
} Vec4;

extern void VecAdd_13be20(Vec4 *, void *, void *);
extern void NodeTransformPoint_1860b0(void *, Vec4 *, Vec4 *);
extern void sceVu0CopyVector(void *, void *);

extern f32 D_0047F910;
extern f32 D_0047F914;
extern f32 D_0047F918;
extern f32 D_0047F91C;

void EvMapObjPartMoveToNode_3640a0(u8 *o, void *p, void *q)
{
    Vec4 v70, v60, v50, v40;

    v70.f[0] = D_0047F910;
    v70.f[1] = D_0047F914;
    v70.f[2] = D_0047F918;
    v70.f[3] = D_0047F91C;
    VecAdd_13be20(&v60, o + 0xC0, q);
    VecAdd_13be20(&v50, o + 0xD0, q);
    VecAdd_13be20(&v40, o + 0xE0, q);
    VecAdd_13be20(&v70, &v70, q);
    NodeTransformPoint_1860b0(p, &v60, &v60);
    NodeTransformPoint_1860b0(p, &v50, &v50);
    NodeTransformPoint_1860b0(p, &v40, &v40);
    NodeTransformPoint_1860b0(p, &v70, &v70);
    *(f32 *)(o + 0x20) = *(f32 *)(o + 0x00);
    *(f32 *)(o + 0x24) = *(f32 *)(o + 0x04);
    *(f32 *)(o + 0x28) = *(f32 *)(o + 0x08);
    *(f32 *)(o + 0x60) = *(f32 *)(o + 0x40);
    *(f32 *)(o + 0x64) = *(f32 *)(o + 0x44);
    *(f32 *)(o + 0x68) = *(f32 *)(o + 0x48);
    *(f32 *)(o + 0xA0) = *(f32 *)(o + 0x80);
    *(f32 *)(o + 0xA4) = *(f32 *)(o + 0x84);
    *(f32 *)(o + 0xA8) = *(f32 *)(o + 0x88);
    *(u128 *)(o + 0x00) = v60.q;
    *(u128 *)(o + 0x40) = v50.q;
    *(u128 *)(o + 0x80) = v40.q;
    sceVu0CopyVector(o + 0x100, o + 0xF0);
    sceVu0CopyVector(o + 0xF0, &v70);
}
