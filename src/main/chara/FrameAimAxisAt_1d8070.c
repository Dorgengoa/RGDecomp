/* MATCH (main s22): the "dead" `addiu $5,$sp,0xB0` in the FrameGetWorldPos_148f30
   delay slot was not a scheduler artefact at all -- FrameGetWorldPos_148f30 takes TWO
   arguments (nine other call sites in the corpus declare it that way) and the
   park was passing one.  A missing argument is invisible to every byte screen
   except the one word the scheduler happened to put in a delay slot. */
#include "types.h"

extern void FrameGetWorldPos_148f30(s32, void *);
extern void VecSub_13be40(void *, s32, void *);
extern void VecNormalize_13bd90(void *, void *);
extern void FrameCalcWorldMatrix_148ff0(s32, void *);
extern void AxisAngleBetweenVecs_1d7da0(void *, f32 *, void *, void *);
extern void VecRotateAxisPair_1d78a0(void *, void *, void *, f32);
extern void FrameCalcInvWorldMatrix_148fb0(s32, void *);
extern void MtxMul_13d240(void *, void *, void *);
extern void ModelFrameSetMatrix_14a190(s32, void *);

void FrameAimAxisAt_1d8070(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    f32 sp14C;
    u8 sp100[0x4C];
    u8 spC0[0x40];
    u8 spB0[0x10];
    u8 spA0[0x10];
    u8 sp90[0x10];
    u8 sp50[0x40];

    if (arg0 != 0) {
        FrameGetWorldPos_148f30(arg0, spB0);
        VecSub_13be40(spA0, arg1, spB0);
        VecNormalize_13bd90(spA0, spA0);
        FrameCalcWorldMatrix_148ff0(arg0, sp100);
        AxisAngleBetweenVecs_1d7da0(sp90, &sp14C, sp100 + (arg2 * 0x10), spA0);
        VecRotateAxisPair_1d78a0(sp100, sp100, sp90, sp14C);
        if (arg3 != 0) {
            FrameCalcInvWorldMatrix_148fb0(arg3, spC0);
            MtxMul_13d240(sp50, spC0, sp100);
        }
        ModelFrameSetMatrix_14a190(arg0, sp50);
    }
}
