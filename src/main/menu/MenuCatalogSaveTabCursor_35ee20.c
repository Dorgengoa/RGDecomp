#include "types.h"
#pragma optimization_level 3

extern void *UiEntryListFindByTag_28ea40(s32, s32);

void MenuCatalogSaveTabCursor_35ee20(void *arg0, s32 arg1)
{
    s32 temp_4;
    u16 var_3;
    u8 *temp_2;

    temp_4 = *(s32 *)((u8 *)arg0 + 0x284);
    if (temp_4 == 3) {
        var_3 = 1;
    } else if (temp_4 == 4) {
        var_3 = 1;
    } else {
        var_3 = 0;
    }
    if (!var_3) {
        temp_2 = (u8 *)UiEntryListFindByTag_28ea40(*(s32 *)((u8 *)arg0 + 0x278), 0x24);
        *(s32 *)((u8 *)arg0 + 0x204) = arg1;
        ((s32 *)((u8 *)arg0 + 0x208))[*(s32 *)((u8 *)arg0 + 0x284) * 2] = *(s16 *)(temp_2 + 0x14);
        ((s32 *)((u8 *)arg0 + 0x20C))[*(s32 *)((u8 *)arg0 + 0x284) * 2] = *(s16 *)(temp_2 + 0x16);
        ((s32 *)((u8 *)arg0 + 0x220))[*(s32 *)((u8 *)arg0 + 0x284) * 2] = *(s16 *)(temp_2 + 0x18);
        ((s32 *)((u8 *)arg0 + 0x224))[*(s32 *)((u8 *)arg0 + 0x284) * 2] = *(s16 *)(temp_2 + 0x1A);
    }
}
