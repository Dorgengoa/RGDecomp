#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad0[0x3A];
    s16 unk3A;
    u8 pad3C[0x44 - 0x3C];
    s32 unk44;
} Obj001dcf20;

typedef struct {
    u8 pad0[0x1A];
    s16 unk1A;
} Obj001e00b0;

extern Obj001dcf20 *MapAreaDefGetRecTable_1dcf20(s32);
extern Obj001e00b0 *MapBlockGetInfo_1e00b0(s32);
extern s16 ScriptArgGetInt_1ecbe0(s32);
extern s32 D_004818F8;
extern const s32 D_004818FC __attribute__((section(".sdata")));
extern const s16 D_00481904 __attribute__((section(".sdata")));


s32 MapDefCmdBlockPlaceNameMsgId_1ebe30(s32 arg0, s32 arg1)
{
    s32 temp_4;
    Obj001e00b0 *temp_16;
    Obj001dcf20 *temp_2;

    switch (arg1) {
    case 1:
        if (D_004818FC == 0 || D_004818F8 == 0) {
            return 1;
        }
        temp_2 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
        temp_4 = temp_2->unk44;
        if (temp_4 == 0 || temp_2->unk3A <= D_00481904) {
            return 1;
        }
        temp_16 = MapBlockGetInfo_1e00b0(temp_4 + (D_00481904 * 0xCC));
        temp_16->unk1A = ScriptArgGetInt_1ecbe0(arg0);
        return 1;
    }
    return 0;
}
