#include "types.h"

extern void TextStyleInitPreset_26c540(void *, s32);
extern void TextStyleInit_26c610(void *);
extern void FontDrawText_26cdc0(void *, s32, s32, s32);
extern s32 FontGetLineHeight_26f3e0(void *);
extern s32 FontGetGlyphWidth_26f420(void *, s32);
extern s32 MesWinGetNameBuf_2712f0(void *);
extern s32 MesWinIsNameShown_271380(void);

void MesWinDrawName_271220(void *arg0) {
    u8 sp40[0x40];
    s32 temp_16;
    s32 temp_17;

    if (MesWinIsNameShown_271380() != 0) {
        TextStyleInit_26c610(sp40);
        TextStyleInitPreset_26c540(sp40, 1);
        temp_17 = FontGetGlyphWidth_26f420(sp40, 0) & 0xFF;
        temp_16 = FontGetLineHeight_26f3e0(sp40) & 0xFF;
        FontDrawText_26cdc0(sp40, MesWinGetNameBuf_2712f0(arg0),
                     *(s32 *)((u8 *)arg0 + 0x40) - temp_17,
                     (*(s32 *)((u8 *)arg0 + 0x44) - temp_16) - 2);
    }
}
