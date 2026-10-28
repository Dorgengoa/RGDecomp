/* rgp:protos */
#define RGP_SELF_MapDefCmdBlockNavGraphId_1ebef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                            /* extern */
/*rgp*/                            /* extern */
/*rgp*/                              /* extern */
/*rgp*/                               /* extern */
/*rgp*/                        /* extern */
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;

s32 MapDefCmdBlockNavGraphId_1ebef0(s32 arg0, s32 arg1) {
    s32 *p;
    s32 temp_4;
    u8 *temp_16;
    u8 *temp_17;
    u8 *temp_2;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    temp_2 = ((u8 *)MapAreaDefGetRecTable_1dcf20(D_004818FC));
    temp_4 = *(s32 *)(temp_2 + 0x44);
    if (temp_4 == 0 || *(s16 *)(temp_2 + 0x3A) <= D_00481904) {
        return 1;
    }
    temp_16 = ((u8 *)MapBlockGetInfo_1e00b0(temp_4 + (D_00481904 * 0xCC)));
    temp_17 = ((u8 *)GetGameData_1fede0());
    p = ((s32 *)TableFindByName_4159e0(*(s32 *)(*(s32 *)(*(s32 *)(temp_17 + 0x8) + 0x34) + 0x18), ScriptArgGetStr_1ecb80(arg0)));
    if (p != 0) {
        *(s32 *)(temp_16 + 0x1C) = *p;
    } else {
        *(s32 *)(temp_16 + 0x1C) = -1;
    }
    return 1;
}
