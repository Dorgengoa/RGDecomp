#include "types.h"

typedef struct Obj001517B0 {
    s32 unk0;
    u8 pad4[0x104 - 0x4];
    s32 unk104;
    u8 pad108[0x10C - 0x108];
    s32 unk10C;
    s32 *unk110;
} Obj001517B0;

extern s32 ArrayGetChecked_152fd0(s32, s32);
extern void ModelFrameSetPosLink_14a530(s32, void *);
extern void ModelFrameSetRotLink_14a500(s32, void *);
extern void ModelFrameSetScaleLink_14a4e0(s32, void *);

s32 ModelBindRootFrameXformsMaybe_1517b0(Obj001517B0 *arg0)
{
    s32 t;
    s32 i;

    if (arg0->unk110 == 0 || arg0->unk0 == 0) {
        return 0;
    }
    for (i = 0; i < arg0->unk10C; i++) {
        t = ArrayGetChecked_152fd0(arg0->unk104, arg0->unk110[i]);
        if (t != 0) {
            ModelFrameSetPosLink_14a530(t, (u8 *)arg0 + 0x180);
            ModelFrameSetRotLink_14a500(t, (u8 *)arg0 + 0x190);
            ModelFrameSetScaleLink_14a4e0(t, (u8 *)arg0 + 0x1A0);
        }
    }
    return 1;
}
