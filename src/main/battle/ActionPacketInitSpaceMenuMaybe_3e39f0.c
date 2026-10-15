#include "types.h"

extern void ActionPacketClear_3e3e90(void);
extern s32 D_00483994;

typedef struct Msg {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 pad4[8];
    s32 unkC;
} Msg;

Msg *ActionPacketInitSpaceMenuMaybe_3e39f0(Msg *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_00483994 == 0) {
        return NULL;
    }
    ActionPacketClear_3e3e90();
    arg0->unk2 = 3;
    if (arg2 != 0) {
        if (arg3 != 0) {
            arg0->unk3 = 0x44;
        } else {
            arg0->unk3 = 0x3B;
        }
    } else {
        arg0->unk3 = 0x3C;
    }
    arg0->unk0 = 2;
    arg0->unkC = arg1;
    return arg0;
}
