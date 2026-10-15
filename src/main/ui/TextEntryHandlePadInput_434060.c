#include "types.h"

extern u8 D_004B2570[0x400];
s32 PadIsTriggered_1839f0(void *, s32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
void TextEntryTogglePage_434230(u8 *);
void TextEntryNameCursorBack_434560(u8 *, s32);
void TextEntryNameCursorAdvance_434690(u8 *, s32);

s32 TextEntryHandlePadInput_434060(u8 *arg0) {
    u8 *d;

    d = D_004B2570;
    if (*(s16 *)(arg0 + 0xE0) == 4) {
        return 1;
    }
    if (PadIsTriggered_1839f0(d, 1) != 0) {
        TextEntryTogglePage_434230(arg0);
    } else if (PadIsTriggered_1839f0(d, 8) != 0) {
        TextEntryNameCursorAdvance_434690(arg0, UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 4), 0x6D62));
    } else if (PadIsTriggered_1839f0(d, 4) != 0) {
        TextEntryNameCursorBack_434560(arg0, UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 4), 0x6D62));
    }
    return 1;
}
