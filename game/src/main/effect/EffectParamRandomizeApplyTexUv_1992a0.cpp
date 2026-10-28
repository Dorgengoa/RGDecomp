/* rgp:protos */
#line 1
/* PARK: m2c cannot decompile -- "Unable to determine jump table for jr
   instruction." Needs a jump-table reconstruction pass this lane's budget
   does not cover. Not attempted. */
/* s49m: MATCH (two-entry, multi-.text scored with agent15/mscore.py) */
#include "types.h"
#include "vec.h"

struct Obj {
    VC_VPTR_MEMBER;
    
      /* +0x10 */
};

extern "C" void __attribute__((naked)) EffectParamRandomizeApplyTexUv_1992a0(Obj *o, void *a)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void CopyQword_18bb60(u8 *, u8 *);
extern "C" f32 RandFloat_1980f0(u8 *);
extern "C" f32 RandGaussian_197d70(u8 *);
extern "C" void VecAddThunk_13be20(u8 *, u8 *, Vec4 *);
extern "C" f32 D_0047D420;

extern "C" void func_001992A0_e1(u8 *self, u8 *other)
{
    Vec4 v __attribute__((aligned(16)));
    s32 i;
    s32 m;

    if (*(s32 *)(self + 0x10) <= 0) {
        CopyQword_18bb60(other + 0x50, self + 0x20);
        return;
    }
    VEC4_ZERO(v);
    if (*(s32 *)(self + 0x10) == 1) {
        for (i = 0; i < 2; i++) {
            (&v.x)[i] = *(f32 *)(self + 0x30 + i * 4) * (2.0f * (RandFloat_1980f0(other + 4) - 0.5f));
        }
    } else if (*(s32 *)(self + 0x10) == 2) {
        for (i = 0; i < 2; i++) {
            (&v.x)[i] = *(f32 *)(self + 0x30 + i * 4) * (D_0047D420 * RandGaussian_197d70(other + 4));
        }
    }
    switch (*(s32 *)(self + 0x14)) {
    case 1:
        v.y = v.x;
        v.z = v.x;
        break;
    case 2:
        v.y = v.x;
        break;
    case 3:
        v.z = v.x;
        break;
    case 4:
        v.z = v.y;
        break;
    case 0:
        break;
    }
    VecAddThunk_13be20(other + 0x50, self + 0x20, &v);
}
