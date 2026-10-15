#include "types.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
    u8 padA[6];
    s16 unk10;
} T002B7A30;

extern s32 PadIsTriggered_1839f0(void *arg0, s32 arg1);
extern s32 PadIsRepeatTriggered_183dd0(void *arg0, s32 arg1);
extern void MenuGridCursorRequestSe_28e9e0(s32 arg0, s32 arg1);
extern void MenuPartySwapCursorUpdateCbMaybe_2b7b50(T002B7A30 *arg0, s32 arg1);
extern s32 D_00482364;
extern u8 D_004B2570[0x400];

s32 MenuPartySwapCursorInputCbMaybe_2b7a30(T002B7A30 *arg0, s32 arg1)
{
    s32 r;

    r = 0;
    if (PadIsTriggered_1839f0(D_004B2570, 8) != 0) {
        if (arg0->unk10 < arg0->unk8) {
            arg0->unk10++;
            r = 1;
        } else if (arg0->unk8 > 0 && PadIsRepeatTriggered_183dd0(D_004B2570, 8) == 0) {
            arg0->unk10 = 0;
            r = 1;
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 4) != 0) {
        if (arg0->unk10 > 0) {
            arg0->unk10--;
            r = 1;
        } else if (arg0->unk8 > 0 && PadIsRepeatTriggered_183dd0(D_004B2570, 4) == 0) {
            arg0->unk10 = arg0->unk8;
            r = 1;
        }
    }
    if (r != 0) {
        MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        MenuPartySwapCursorUpdateCbMaybe_2b7b50(arg0, arg1);
    }
    return 1;
}
