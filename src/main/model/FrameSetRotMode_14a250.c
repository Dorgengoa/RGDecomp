#include "types.h"
/* FrameSetRotMode_14a250 -- asm-free (s88m): lazily binds o->pos to the embedded o->buf (init w=1 if 0),
 * sets flags 0x2B=1/0x29=1/0x2C=0 and clears pos.xyz from a zeroed stack quad (CopyXYZ, as in
 * FrameSetRot_14a390), then stores pos->w = val.  The zeroing lives in a static inline helper so the
 * stack address is materialised (addiu v1,sp,0); opt_propagation off keeps the shared `1`. */
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz14a250 asm("vf0");
extern u128 va14a250 asm("vf1");
extern u128 vb14a250 asm("vf2");

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
    va14a250 = *(volatile u128 *)pd;
    vb14a250 = *(volatile u128 *)ps;
    va14a250 = _vaddbc(va14a250, 0xE, vb14a250, vz14a250, 8);
    *pd = va14a250;
}
#pragma opt_propagation off
static inline void SetZero(Obj *o)
{
    u128 z = 0;
    CopyXYZ(o->pos, &z);
}
void FrameSetRotMode_14a250(Obj *o, s32 val)
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
        SetZero(o);
    }
    o->pos->init = val;
}
