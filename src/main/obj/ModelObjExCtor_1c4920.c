#include "types.h"

#pragma opt_loop_invariants off

extern void ModelObjShadowFrameMapCtor_195450(void *);
extern void ModelCtor_195470(void *);
extern void ModelAttachSlotCtor_1954c0(void *);
extern void ModelObjBaseCtor_1954e0(void);
extern void MotionEventListClear_1b4aa0(void *, s32);
extern void *memset(void *, s32, s32);

extern u8 D_00470ED0[];
extern u8 D_00470FB0[];
extern u8 D_00471140[];
extern u8 D_00471160[];
extern u8 D_00471180[];
extern u8 D_004711A0[];
extern u8 D_004711C0[];
extern u8 D_004711E0[];

typedef struct Obj001c4920 {
    u8 pad0[0x1B0];
    void *unk1B0;
    u8 pad1B4[0x4F0 - 0x1B4];
    s32 unk4F0;
    u8 pad4F4[0x4F8 - 0x4F4];
    s32 unk4F8;
    s32 unk4FC;
    s32 unk500;
    s32 unk504;
    f32 unk508;
    s32 unk50C;
    s32 unk510;
    s32 unk514;
    s32 unk518;
    u8 pad51C[0x548 - 0x51C];
    s32 unk548;
    s32 unk54C;
    s32 unk550;
    u8 pad554[0x570 - 0x554];
    void *unk570;
    s32 unk574;
    void *unk578;
    s32 unk57C;
    void *unk580;
    s32 unk584;
    void *unk588;
    s32 unk58C;
} Obj001c4920;

void *ModelObjExCtor_1c4920(Obj001c4920 *arg0)
{
    u8 *var_18;
    u8 *var_17;

    ModelObjBaseCtor_1954e0();
    var_18 = (u8 *)arg0 + 0x228;
    arg0->unk1B0 = D_00470ED0;
    do {
        ModelAttachSlotCtor_1954c0(var_18);
        var_18 += 8;
        var_17 = (u8 *)arg0 + 0x248;
    } while (var_18 < var_17);
    do {
        ModelAttachSlotCtor_1954c0(var_17);
        var_17 += 8;
    } while (var_17 < (u8 *)arg0 + 0x268);
    ModelCtor_195470((u8 *)arg0 + 0x270);
    ModelObjShadowFrameMapCtor_195450((u8 *)arg0 + 0x430);
    arg0->unk1B0 = D_00470FB0;
    memset((u8 *)arg0 + 0x4F0, 0, 0x2C);
    arg0->unk4F0 = -1;
    arg0->unk4FC = -1;
    arg0->unk500 = -1;
    arg0->unk4F8 = 1;
    arg0->unk504 = 1;
    arg0->unk508 = 1.0f;
    arg0->unk50C = 0;
    arg0->unk510 = -1;
    arg0->unk514 = 0;
    arg0->unk518 = 0;
    arg0->unk548 = 0;
    arg0->unk54C = 0;
    arg0->unk550 = 0;
    MotionEventListClear_1b4aa0((u8 *)arg0 + 0x568, -1);
    arg0->unk570 = D_004711E0;
    arg0->unk570 = D_004711C0;
    arg0->unk574 = 0;
    arg0->unk570 = D_004711A0;
    arg0->unk578 = D_004711E0;
    arg0->unk578 = D_004711C0;
    arg0->unk57C = 0;
    arg0->unk578 = D_00471180;
    arg0->unk580 = D_004711E0;
    arg0->unk580 = D_004711C0;
    arg0->unk584 = 0;
    arg0->unk580 = D_00471160;
    arg0->unk588 = D_004711E0;
    arg0->unk588 = D_004711C0;
    arg0->unk58C = 0;
    arg0->unk588 = D_00471140;
    return arg0;
}
