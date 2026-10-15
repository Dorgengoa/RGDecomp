#include "types.h"
/* FrameSetRot_14a390 -- asm-free (s88m): lazily binds o->pos to the embedded o->buf, then
 * copies v.xyz into it (keeping w) when it differs.  The old asm source's CopyXYZ
 * (vaddx.xyz vfA, vfB, vf0x) is spelled with mwcc VU0 intrinsics on extern bindings.
 * - volatile u128 loads keep the dest-then-source lqc2 order;
 * - the volatile re-read of o->pos defeats CSE with the compare's pointer (retail reload);
 * - the `if (o) o = launder(o)` block split keeps `li 1` after the sqc2. */

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz14a390 asm("vf0");
extern u128 va14a390 asm("vf1");
extern u128 vb14a390 asm("vf2");

typedef struct Vec3 {
    f32 x, y, z;
    s32 init;
} Vec3;

typedef struct Obj {
    u8 pad0[0x18];
    Vec3 *pos;
    u8 pad1c[0xD];
    u8 dirty;
    u8 pad2a;
    u8 flag2b;
    u8 flag2c;
    u8 pad2d[0x13];
    Vec3 buf;
} Obj;

static inline void CopyXYZ(void *d, void *s)
{
    u128 *pd = (u128 *)d;
    u128 *ps = (u128 *)s;
    va14a390 = *(volatile u128 *)pd;
    vb14a390 = *(volatile u128 *)ps;
    va14a390 = _vaddbc(va14a390, 0xE, vb14a390, vz14a390, 8);
    *pd = va14a390;
}

void FrameSetRot_14a390(Obj *o, Vec3 *v)
{
    Vec3 *p;

    if (o->pos == 0) {
        p = &o->buf;
        o->pos = p;
        if (p != 0) {
            s32 *ip = &p->init;
            if (*ip == 0) {
                *ip = 1;
            }
        }
        o->flag2b = 1;
        o->dirty = 1;
        o->flag2c = 0;
        o->pos->init = 1;
        CopyXYZ(o->pos, v);
        o->dirty = 1;
    } else if (o->pos->x != v->x || o->pos->y != v->y || o->pos->z != v->z) {
        CopyXYZ(*(Vec3 * volatile *)&o->pos, v);
        if (o) {
            o = (Obj *)(s32)(u32)o;
        }
        o->dirty = 1;
    }
}
