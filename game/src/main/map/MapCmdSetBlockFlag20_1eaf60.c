/* rgp:protos */
#define RGP_SELF_MapCmdSetBlockFlag20_1eaf60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004818F8;
extern s32 D_004818FC;

s32 MapCmdSetBlockFlag20_1eaf60(s32 arg0, s32 arg1) {
    u8 *t;
    u8 *u;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    t = (u8 *)MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if (*(s32 *)(t + 0x44) == 0 || *(s16 *)(t + 0x3A) <= 0) {
        return 1;
    }
    u = (u8 *)MapRecTableFindBlockByName_1dd270(t, ScriptArgGetStr_1ecb80(arg0));
    if (u == NULL) {
        return 1;
    }
    *(s32 *)(u + 0x2C) |= 0x20;
    return 1;
}
