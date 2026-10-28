/* rgp:protos */
#define RGP_SELF_MesWinDrawName_271220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinDrawName_271220(void *arg0) {
    u8 sp40[0x40] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_17;

    if (((short)MesWinIsNameShown_271380((void *)arg0)) != 0) {
        TextStyleInit_26c610(sp40);
        TextStyleInitPreset_26c540(sp40, 1);
        temp_17 = FontGetGlyphWidth_26f420(sp40, 0) & 0xFF;
        temp_16 = FontGetLineHeight_26f3e0(sp40) & 0xFF;
        FontDrawText_26cdc0(sp40, ((s32)MesWinGetNameBuf_2712f0(arg0)),
                     *(s32 *)((u8 *)arg0 + 0x40) - temp_17,
                     (*(s32 *)((u8 *)arg0 + 0x44) - temp_16) - 2);
    }
}
