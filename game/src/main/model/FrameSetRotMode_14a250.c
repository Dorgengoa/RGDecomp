/* rgp:protos */
#define RGP_SELF_CopyXYZ 1
#define RGP_SELF_FrameSetRotMode_14a250 1
#define RGP_SELF_SetZero 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
/* FrameSetRotMode_14a250 -- asm-free (s88m): lazily binds o->pos to the embedded o->buf (init w=1 if 0),
 * sets flags 0x2B=1/0x29=1/0x2C=0 and clears pos.xyz from a zeroed stack quad (CopyXYZ, as in
 * FrameSetRot_14a390), then stores pos->w = val.  The zeroing lives in a static inline helper so the
 * stack address is materialised (addiu v1,sp,0); opt_propagation off keeps the shared `1`. */
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz14a250_t; /* rg:vu0bind vf0 */
#define vz14a250 RG_VU0_BIND_VF(0, rgvb_vz14a250_t)

typedef u128 __attribute__((aligned(4))) rgvb_va14a250_t; /* rg:vu0bind vf1 */
#define va14a250 RG_VU0_BIND_VF(1, rgvb_va14a250_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb14a250_t; /* rg:vu0bind vf2 */
#define vb14a250 RG_VU0_BIND_VF(2, rgvb_vb14a250_t)


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

static inline void CopyXYZ(rg_vu0_state *rg_vu0_p_, void *d, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    u128 *pd = (u128 *)d;
    u128 *ps = (u128 *)s;
    va14a250 = *(volatile u128 *)pd;
    vb14a250 = *(volatile u128 *)ps;
    va14a250 = _vaddbc(va14a250, 0xE, vb14a250, vz14a250, 8);
    *pd = va14a250;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}
#pragma opt_propagation off
static inline void SetZero(Obj *o)
{ RG_VU0_FRAME;
    u128 z = 0;
    CopyXYZ(&rg_vu0, o->pos, &z);
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
