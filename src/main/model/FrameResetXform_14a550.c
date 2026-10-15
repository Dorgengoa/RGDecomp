#include "types.h"
#include "vec.h"

/* asm-free (s88m): retail `sqc2 vf0` = u128 store of an extern vf0 binding. */
#pragma vu0_mmi_reg_binding on
extern u128 vz14a550 asm("vf0");

extern void MtxIdentity_13d2e0(void *arg0);

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} __attribute__((aligned(16))) Quad0014A550;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
} FQuad0014A550;

typedef struct {
    u8 pad00[0x14];
    Quad0014A550 *unk14;
    Quad0014A550 *unk18;
    FQuad0014A550 *unk1C;
    u8 pad20[0x29 - 0x20];
    u8 unk29;
} Obj0014A550;

void FrameResetXform_14a550(Obj0014A550 *arg0)
{
    Quad0014A550 *p14;
    Quad0014A550 *p18;
    FQuad0014A550 *p1C;

    MtxIdentity_13d2e0((void *)((u8 *)arg0 + 0x60));

    p14 = arg0->unk14;
    if (p14 != NULL) {
        *(u128 *)p14 = vz14a550;
    }
    p18 = arg0->unk18;
    if (p18 != NULL) {
        *(u128 *)p18 = 0;
        arg0->unk18->unkC = 1;
    }
    p1C = arg0->unk1C;
    if (p1C != NULL) {
        p1C->unk8 = 1.0f;
        arg0->unk1C->unk4 = 1.0f;
        arg0->unk1C->unk0 = 1.0f;
        arg0->unk1C->unkC = 0;
    }
    arg0->unk29 = 1;
}
