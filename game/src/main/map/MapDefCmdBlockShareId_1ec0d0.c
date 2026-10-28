/* rgp:protos */
#define RGP_SELF_MapDefCmdBlockShareId_1ec0d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;

s32 MapDefCmdBlockShareId_1ec0d0(s32 arg0, s32 arg1) {
    s32 sp40[4] __attribute__((aligned(16)));
    u8 *e;
    u8 *m;
    u8 *r;
    s16 v;
    s32 h;

    if (arg1 != 1) {
        return 0;
    }
    if ((D_004818FC == 0) || (D_004818F8 == 0)) {
        return 1;
    }
    m = ((u8 *)MapAreaDefGetRecTable_1dcf20(D_004818FC));
    if ((*(u8 **)(m + 0x44) == NULL) || (*(s16 *)(m + 0x3A) <= D_00481904)) {
        return 1;
    }
    e = *(u8 **)(m + 0x44) + D_00481904 * 0xCC;
    r = ((u8 *)MapBlockGetInfo_1e00b0(e));
    v = ScriptArgGetInt_1ecbe0(arg0);
    *(s16 *)(r + 0x16) = v;
    h = ((s32)MapRecTableFindShareById_1dd4a0(m, v));
    if (h != 0) {
        MapDataGetColorVec4_1e7610(h, sp40);
        MapDataSetColorVec_1e73b0(e, sp40);
    }
    return 1;
}
