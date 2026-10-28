/* rgp:protos */
#define RGP_SELF_CopyXYZ 1
#define RGP_SELF_FrameSetRot_14a390 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
/* FrameSetRot_14a390 -- asm-free (s88m): lazily binds o->pos to the embedded o->buf, then
 * copies v.xyz into it (keeping w) when it differs.  The old asm source's CopyXYZ
 * (vaddx.xyz vfA, vfB, vf0x) is spelled with mwcc VU0 intrinsics on extern bindings.
 * - volatile u128 loads keep the dest-then-source lqc2 order;
 * - the volatile re-read of o->pos defeats CSE with the compare's pointer (retail reload);
 * - the `if (o) o = launder(o)` block split keeps `li 1` after the sqc2. */

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz14a390_t; /* rg:vu0bind vf0 */
#define vz14a390 RG_VU0_BIND_VF(0, rgvb_vz14a390_t)

typedef u128 __attribute__((aligned(4))) rgvb_va14a390_t; /* rg:vu0bind vf1 */
#define va14a390 RG_VU0_BIND_VF(1, rgvb_va14a390_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb14a390_t; /* rg:vu0bind vf2 */
#define vb14a390 RG_VU0_BIND_VF(2, rgvb_vb14a390_t)


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
    va14a390 = *(volatile u128 *)pd;
    vb14a390 = *(volatile u128 *)ps;
    va14a390 = _vaddbc(va14a390, 0xE, vb14a390, vz14a390, 8);
    *pd = va14a390;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

void FrameSetRot_14a390(Obj *o, Vec3 *v)
{ RG_VU0_FRAME;
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
        CopyXYZ(&rg_vu0, o->pos, v);
        o->dirty = 1;
    } else if (o->pos->x != v->x || o->pos->y != v->y || o->pos->z != v->z) {
        CopyXYZ(&rg_vu0, *(Vec3 * volatile *)&o->pos, v);
        if (o) {
            o = (Obj *)(s32)(u32)o;
        }
        o->dirty = 1;
    }
}
