/* rgp:protos */
#line 1
#pragma opt_optimizecontrolflow off
#include "types.h"
extern "C" {
#pragma opt_common_subs off
#pragma no_branch_likely on
/* PARK (round 1): length 0x128 vs retail 0x110. */


#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern f32 VecLengthSq_1cb470(void *, void *);
extern void VecMinMax_1cb570(void *, void *, void *, void *);
extern void VecLinearCombine_1cb8b0(void *, void *, void *, f32, f32);
extern void VecSub_1cbd00(void *, void *, f32 *);
extern void VecAdd_1cbdc0(void *, void *, f32 *);
extern void VecCopyAsPoint_1cbe10(void *, void *);
extern void VecCopyAsDir_1cbe20(void *, s32);

void CollSweepInit_1c81b0(void *arg0, s32 gpt_unused0, s32 arg2, f32 fparg0, f32 fparg1)
{






u8 sp50[16] __attribute__((aligned(16)));f32 vec[4] __attribute__((aligned(16)));
    u8 *var_3;
    f32 temp_f0;
    f32 var_f21;
    u32 var_2;

    var_f21 = fparg0;
    VecCopyAsPoint_1cbe10((void *)arg0, (void *)gpt_unused0);
    VecCopyAsDir_1cbe20((u8 *)arg0 + 0x10, arg2);
    if (var_f21 < 0.0f) {
        var_f21 = -var_f21;
    }
    F32(arg0, 0x20) = var_f21;
    F32(arg0, 0x70) = var_f21 * var_f21;
    F32(arg0, 0x74) = VecLengthSq_1cb470((u8 *)arg0 + 0x10, 0);
    F32(arg0, 0x24) = fparg1;
    VecLinearCombine_1cb8b0(sp50, (u8 *)arg0 + 0x10, arg0, F32(arg0, 0x24), 1.0f);
    VecMinMax_1cb570((u8 *)arg0 + 0x40, (u8 *)arg0 + 0x30, arg0, sp50);
    var_3 = (u8*)vec;
    var_2 = 0x10;
    if (var_3 != NULL) {
        do {
            *var_3 = 0;
            var_2 -= 1;
            var_3 += 1;
        } while (var_2 != 0);
    }
    temp_f0 = F32(arg0, 0x20);
    vec[0] = temp_f0;
    vec[1] = temp_f0;
    vec[2] = temp_f0;
    VecAdd_1cbdc0((u8 *)arg0 + 0x60, (u8 *)arg0 + 0x40, vec);
    VecSub_1cbd00((u8 *)arg0 + 0x50, (u8 *)arg0 + 0x30, vec);
}

}
