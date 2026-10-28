/* rgp:protos */
#define RGP_SELF_MapDefCmdBlockColor_1eba90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;

s32 MapDefCmdBlockColor_1eba90(s32 arg0, s32 arg1)
{
    u8 *p;
    s32 q;
    s32 base;
    s32 a;
    s32 b;
    s32 c;
    s32 x;
    s32 k;

    if (arg1 != 4) {
        return 1;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    p = ((u8 *)MapAreaDefGetRecTable_1dcf20(D_004818FC));
    q = *(s32 *)(p + 0x44);
    if (q == 0 || !(*(s16 *)(p + 0x3A) > D_00481904)) {
        return 1;
    }
    base = q + D_00481904 * 0xCC;
    a = ScriptArgGetInt_1ecbe0(arg0);
    b = ScriptArgGetInt_1ecbe0(arg0 + 8);
    c = ScriptArgGetInt_1ecbe0(arg0 + 0x10);
    MapDataSetColor_1e72d0(base, a, b, c, ScriptArgGetInt_1ecbe0(arg0 + 0x18));
    return 1;
}
