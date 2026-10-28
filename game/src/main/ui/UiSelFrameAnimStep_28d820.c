/* rgp:protos */
#define RGP_SELF_UiSelFrameAnimStep_28d820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    u8 pad2[0x10 - 0x2];
    f32 unk10;
    u8 pad14[0x18 - 0x14];
    s16 unk18;
    u8 pad1a[0x20 - 0x1a];
    s16 unk20;
    s16 unk22;
    u8 pad24[0x30 - 0x24];
    f32 unk30;
    u8 pad34[0x38 - 0x34];
    s16 unk38;
    u8 pad3a[0x42 - 0x3a];
    s16 unk42;
    u8 pad44[0x54 - 0x44];
    f32 unk54;
    u8 pad58[0x5a - 0x58];
    s16 unk5A;
    u8 pad5c[0x60 - 0x5c];
    s16 unk60;
    s16 unk62;
    u8 pad64[0x74 - 0x64];
    f32 unk74;
    s16 unk78_pad;
    s16 unk7A;
} Sub;

typedef struct {
    u8 pad0[0x20];
    Sub *unk20;
} Ret;

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE[0x18 - 0xE];
    s32 unk18;
    s32 unk1C;
} Obj;

/*rgp*/

void UiSelFrameAnimStep_28d820(Obj *arg0, s32 arg1) {
    Sub *p;

    arg0->unk6 = arg0->unk6 + 1;
    if (arg0->unk6 == arg0->unkC) {
        arg0->unk6 = 0;
        arg0->unk4 = arg0->unk4 + 1;
        p = ((Ret *)UiFindWidget_290460(arg0->unk0, arg1))->unk20;
        p->unk0 = p->unk0 + 1;
        if (arg0->unk4 == 0x10) {
            p->unk0 = p->unk0 - 0x10;
        }
        p->unk10 = arg0->unk8 + 1;
        p->unk18 = 0x10;
        p->unk22 = arg0->unk1C + 0x10;
        p->unk20 = p->unk20 - 1;
        if (arg0->unk4 == 0x10) {
            p->unk20 = p->unk20 + 0x10;
        }
        p->unk30 = arg0->unk8 + 1;
        p->unk38 = 0x10;
        p->unk42 = p->unk42 - 1;
        if (arg0->unk4 == 0x10) {
            p->unk42 = p->unk42 + 0x10;
        }
        p->unk54 = arg0->unkA + 1;
        p->unk5A = 0x10;
        p->unk60 = arg0->unk18 + 0x10;
        p->unk62 = p->unk62 + 1;
        if (arg0->unk4 == 0x10) {
            p->unk62 = p->unk62 - 0x10;
        }
        p->unk74 = arg0->unkA + 1;
        p->unk7A = 0x10;
        if (arg0->unk4 == 0x10) {
            arg0->unk4 = 0;
        }
    }
}
