#include "types.h"

extern void FrameSetScale_14a2c0(void *b, void *p);
extern void ModelFrameSetRotQuat_14a130(void *b, void *p);
extern void MtxIdentity_13d2e0(void *dst);
extern void MatRotateVu0_13bc20(void *mat, void *vec);
extern void ModelFrameSetRotMatrix_14a160(void *dst, void *mat);
extern void FrameSetDirty_14a5e0(void *p);

void AnimSlotApplyToFrame_154580(u8 *a, u8 *b)
{
    u8 buf[0x40];

    if (*(s32 *)(a + 0xc) != 0) {
        FrameSetScale_14a2c0(b, a + 0x40);
    }

    if (*(s32 *)(a + 0x0) != 0) {
        ModelFrameSetRotQuat_14a130(b, a + 0x50);
    } else if (*(s32 *)(a + 0x4) != 0) {
        MtxIdentity_13d2e0(buf);
        MatRotateVu0_13bc20(buf, a + 0x30);
        ModelFrameSetRotMatrix_14a160(b, buf);
    }

    if (*(s32 *)(a + 0x8) != 0) {
        *(f32 *)(b + 0x90) = *(f32 *)(a + 0x20);
        *(f32 *)(b + 0x94) = *(f32 *)(a + 0x24);
        *(f32 *)(b + 0x98) = *(f32 *)(a + 0x28);
        FrameSetDirty_14a5e0(b);
    }

    if (*(s32 *)(a + 0x10) != 0) {
        *(u8 *)(b + 0x24) = *(s32 *)(a + 0x14);
    }
}
