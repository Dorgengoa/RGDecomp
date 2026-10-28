/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetRefCmd_23dd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004BCE60[0x400];
extern u8 D_004BCE8C[0x400];

s32 CharaEffEntrySetRefCmd_23dd90(s32 arg0, s32 arg1)
{
    s32 sp2C;
    s32 sp28;
    s32 temp_16;

    if ((arg1 != 0) && (arg1 != 1) && (arg1 != 2)) {
        return 0;
    }
    if ((*(s32 *)D_004BCE60) == 0 || (*(s16 *)D_004BCE8C) >= 0x80) {
        return 1;
    }
    sp28 = 0;
    temp_16 = (*(s32 *)D_004BCE60) + (*(s16 *)D_004BCE8C) * 0x7C;
    sp2C = -1;
    if (ScriptParseIntStrArgs_23de60(&sp2C, &sp28, arg0, arg1) != 0) {
        CharaEffEntrySetRefPos_230120(temp_16, sp2C, sp28);
        CharaEffEntrySetRefRot_230100(temp_16, sp2C, sp28);
    }
    return 1;
}
