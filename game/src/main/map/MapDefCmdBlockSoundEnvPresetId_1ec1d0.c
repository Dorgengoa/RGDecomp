/* rgp:protos */
#define RGP_SELF_MapDefCmdBlockSoundEnvPresetId_1ec1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode off

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;
s32 MapDefCmdBlockSoundEnvPresetId_1ec1d0(s32 arg0, s32 arg1) {
    u8 *temp_2;
    u8 *temp_4;
    u8 *temp_17;
    u8 *temp_16;

    if (arg1 <= 0) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    temp_2 = (u8 *)MapAreaDefGetRecTable_1dcf20(D_004818FC);
    temp_4 = *(u8 **)(temp_2 + 0x44);
    if (temp_4 == NULL || *(s16 *)(temp_2 + 0x3A) <= D_00481904) {
        return 1;
    }
    temp_17 = temp_4 + D_00481904 * 0xCC;
    temp_16 = (u8 *)MapBlockGetInfo_1e00b0(temp_17);
    *(s32 *)(temp_17 + 0x2C) |= 8;
    *(s16 *)(temp_16 + 0x14) = ScriptArgGetInt_1ecbe0(arg0);
    return 1;
}
