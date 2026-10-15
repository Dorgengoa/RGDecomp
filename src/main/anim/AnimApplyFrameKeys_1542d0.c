/* MATCH (s41m). Stale pre-match note follows -- PARK candidate on first score -- many m2c stack fields (sp94/98/9C/A0/A4/B0/B4/B8)
   were undeclared in the draft; modeled as one output struct at sp90. */
#include "types.h"

typedef struct Out {
    s32 f0;   /* sp90 */
    s32 f4;   /* sp94 */
    s32 f8;   /* sp98 */
    s32 fC;   /* sp9C */
    s32 f10;  /* spA0 */
    s32 f14;  /* spA4 */
    u8  pad18[0x8];
    f32 f30;  /* spB0 */
    f32 f34;  /* spB4 */
    f32 f38;  /* spB8 */
} Out;

extern void MatRotateVu0_13bc20(void *, void *);
extern void MtxIdentity_13d2e0(void *);
extern void ModelFrameSetRotQuat_14a130(void *, void *);
extern void ModelFrameSetRotMatrix_14a160(void *, void *);
extern void FrameSetScale_14a2c0(void *, void *);
extern void FrameSetDirty_14a5e0(void *);
extern void *AnimResGetFrameKeyList_14bf10(s32);
extern void *ArrayGetChecked_152fd0(s32, u16);
extern void AnimKeyEvalFrame_155e10(Out *, void *, f32);

s32 AnimApplyFrameKeys_1542d0(s32 arg0, s32 arg1, f32 fparg0)
{
    void *var_17;
    void *temp_2;
    u8 spE0[0x10];
    u8 spD0[0x10];
    u8 spC0[0x10];
    Out sp90;
    u8 sp50[0x40];

    if (arg0 == 0) {
        return 0;
    }
    var_17 = AnimResGetFrameKeyList_14bf10(arg1);
    while (var_17 != NULL) {
        temp_2 = ArrayGetChecked_152fd0(arg0, *(u16 *)((u8 *)var_17 + 4));
        if (temp_2 != NULL) {
            AnimKeyEvalFrame_155e10(&sp90, var_17, fparg0);
            if (sp90.fC != 0) {
                FrameSetScale_14a2c0(temp_2, spD0);
            }
            if (sp90.f0 != 0) {
                ModelFrameSetRotQuat_14a130(temp_2, spE0);
            } else {
                if (sp90.f4 != 0) {
                    MtxIdentity_13d2e0(sp50);
                    MatRotateVu0_13bc20(sp50, spC0);
                    ModelFrameSetRotMatrix_14a160(temp_2, sp50);
                }
            }
            if (sp90.f8 != 0) {
                *(f32 *)((u8 *)temp_2 + 0x90) = sp90.f30;
                *(f32 *)((u8 *)temp_2 + 0x94) = sp90.f34;
                *(f32 *)((u8 *)temp_2 + 0x98) = sp90.f38;
                FrameSetDirty_14a5e0(temp_2);
            }
            if (sp90.f10 != 0) {
                *((u8 *)temp_2 + 0x24) = (s8) sp90.f14;
            }
        }
        var_17 = *(void **)var_17;
    }
    return 1;
}
