/* rgp:protos */
#define RGP_SELF_CopyXYZ 1
#define RGP_SELF_ModelSetPos_151110 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "vec.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz151110_t; /* rg:vu0bind vf0 */
#define vz151110 RG_VU0_BIND_VF(0, rgvb_vz151110_t)

typedef u128 __attribute__((aligned(4))) rgvb_va151110_t; /* rg:vu0bind vf1 */
#define va151110 RG_VU0_BIND_VF(1, rgvb_va151110_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb151110_t; /* rg:vu0bind vf2 */
#define vb151110 RG_VU0_BIND_VF(2, rgvb_vb151110_t)



/* self+0x180 is a Vec4 slot that gets XY(Z) replaced from `other` only when
   it actually differs (Vec3NotEqual_14a930 does a component-wise f32 compare of
   two 3-float structs and returns 0 iff equal -- see src/world/ModelGetRootFrame_1511a0.c
   and src/p23a/Vec3NotEqual_14a930.c for the same accessor pair, same offsets
   0x104/0x10C/0x110 on what is evidently the same object type). The VU0
   copy (vaddx.xyz dst,src,vf0x, vf0.x==0.0) keeps dst's existing .w and only
   replaces .xyz. Asm-free (s88m): spelled with mwcc VU0 intrinsics on extern
   vf0/vf1/vf2 bindings; volatile u128 loads keep the dest-then-source lqc2
   order, and the zero-word `if (self) self = launder(self)` block splits on
   both sides of the copy stand in for the old asm block's scheduling barrier.

   The list-scan loop's second call is the "leftover argument register is a
   real argument" lever: FrameSetDirty_14a5e0 is called with NO explicit arg setup
   in its jal's delay slot (a bare nop) -- what it actually receives is
   $4 == the still-live return value of the ArrayGetChecked_152fd0 call just before
   it (retail's `daddu $4,$2,$0` copies v0 into a0 right after the call,
   then never touches $4 again before the conditional jal). */

typedef struct {
    u8 pad000[0x104];
    s32 unk104;
    u8 pad108[0x10C - 0x108];
    s32 unk10C;
    s32 *unk110;
    u8 pad114[0x180 - 0x114];
    Vec4 unk180;
} T_00150ff0;

static inline void CopyXYZ(rg_vu0_state *rg_vu0_p_, void *d, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    u128 *pd = (u128 *)d;
    u128 *ps = (u128 *)s;
    va151110 = *(volatile u128 *)pd;
    vb151110 = *(volatile u128 *)ps;
    va151110 = _vaddbc(va151110, 0xE, vb151110, vz151110, 8);
    *pd = va151110;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/*rgp*/
/*rgp*/
/*rgp*/

void ModelSetPos_151110(T_00150ff0 *self, Vec4 *other)
{ RG_VU0_FRAME;
    s32 i;
    s32 v;

    if (Vec3NotEqual_14a930(&self->unk180, other) == 0) {
        return;
    }

    if (self) { self = (T_00150ff0 *)(s32)(u32)self; }
    CopyXYZ(&rg_vu0, &self->unk180, other);
    if (self) { self = (T_00150ff0 *)(s32)(u32)self; }

    i = 0;
    while (i < self->unk10C) {
        v = ArrayGetChecked_152fd0(self->unk104, self->unk110[i]);
        if (v != 0) {
            FrameSetDirty_14a5e0((void *)v);
        }
        i++;
    }
}
