/* rgp:protos */
#define RGP_SELF_TextEntryHandlePadInput_434060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004B2570[0x400];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TextEntryHandlePadInput_434060(u8 *arg0) {
    u8 *d;

    d = D_004B2570;
    if (*(s16 *)(arg0 + 0xE0) == 4) {
        return 1;
    }
    if (PadIsTriggered_1839f0(d, 1) != 0) {
        TextEntryTogglePage_434230(arg0);
    } else if (PadIsTriggered_1839f0(d, 8) != 0) {
        TextEntryNameCursorAdvance_434690(arg0, ((s32)UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 4), 0x6D62)));
    } else if (PadIsTriggered_1839f0(d, 4) != 0) {
        TextEntryNameCursorBack_434560(arg0, ((s32)UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 4), 0x6D62)));
    }
    return 1;
}
