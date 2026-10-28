#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    u8 pad0[8];
    s16 m8;
    s16 mA;
    u8 padC[4];
    s16 m10;
    s16 m12;
} Cur434f40;

typedef struct {
    u8 pad0[0x14];
    s32 m14;
} Pad434f40;

typedef struct {
    u8 pad0[4];
    Pad434f40 *m4;
} Obj434f40;

extern "C" {
Cur434f40 *UiEntryListGetCurrentData_28ec60(Pad434f40 *);
s32 PadIsRepeatTriggered_183dd0(u8 *, s32);
s16 TextEntryGridFindValidCellMaybe_433e90(void *, s8 *, s16, s16, s16);
void PadRestartRepeat_28e900(Pad434f40 *, u8 *, s32);
extern u8 D_004B2570[];
}

extern "C" void TextEntryCursorWrapEdges_434f40(Obj434f40 *arg0, s8 *arg1, s16 *arg2)
{
    Cur434f40 *cur;
    bool moved;
    s16 p;

    cur = UiEntryListGetCurrentData_28ec60(arg0->m4);
    moved = false;
    if ((arg0->m4->m14 & 4) && PadIsRepeatTriggered_183dd0(D_004B2570, 0x8000) == 0) {
        cur->m10 = cur->m8;
        p = TextEntryGridFindValidCellMaybe_433e90(arg0, arg1, cur->m10 + cur->m12 * 29, 0, -1);
        cur->m10 = p % 29;
        cur->m12 = p / 29;
        PadRestartRepeat_28e900(arg0->m4, D_004B2570, 0x8000);
        moved = true;
    } else if ((arg0->m4->m14 & 8) && PadIsRepeatTriggered_183dd0(D_004B2570, 0x2000) == 0) {
        cur->m10 = 0;
        p = TextEntryGridFindValidCellMaybe_433e90(arg0, arg1, cur->m10 + cur->m12 * 29, 0, 1);
        cur->m10 = p % 29;
        cur->m12 = p / 29;
        PadRestartRepeat_28e900(arg0->m4, D_004B2570, 0x2000);
        moved = true;
    }
    if ((arg0->m4->m14 & 1) && PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000) == 0) {
        cur->m12 = cur->mA;
        p = TextEntryGridFindValidCellMaybe_433e90(arg0, arg1, cur->m10 + cur->m12 * 29, 1, -29);
        cur->m10 = p % 29;
        cur->m12 = p / 29;
        PadRestartRepeat_28e900(arg0->m4, D_004B2570, 0x1000);
        moved = true;
    } else if ((arg0->m4->m14 & 2) && PadIsRepeatTriggered_183dd0(D_004B2570, 0x4000) == 0) {
        cur->m12 = 0;
        p = TextEntryGridFindValidCellMaybe_433e90(arg0, arg1, cur->m10 + cur->m12 * 29, 1, 29);
        cur->m10 = p % 29;
        cur->m12 = p / 29;
        PadRestartRepeat_28e900(arg0->m4, D_004B2570, 0x4000);
        moved = true;
    }
    if (moved) {
        arg2[0] = cur->m10;
        arg2[1] = cur->m12;
    }
}
