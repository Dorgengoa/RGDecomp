/* rgp:protos */
#define RGP_SELF_MapCmdSetBlockBox_1eb020 1
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
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004818F8;
extern s32 D_004818FC;

s32 MapCmdSetBlockBox_1eb020(s32 arg0, s32 arg1)
{
    void *p;
    s32 q;
    s32 r;
    f32 a;
    f32 b;

    if (arg1 != 2 && arg1 != 8) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    p = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if (*(s32 *)((u8 *)p + 0x44) == 0 || *(s16 *)((u8 *)p + 0x3A) <= 0) {
        return 1;
    }
    q = ((s32)MapRecTableFindBlockByName_1dd270(p, ScriptArgGetStr_1ecb80(arg0)));
    if (q == 0) {
        return 1;
    }
    MapDataSetHeapSize_1e7470(q, ScriptArgGetInt_1ecbe0(arg0 + 8));
    if (arg1 == 2) {
        return 1;
    }
    r = ((s32)MapBlockGetBox_1e00a0(q));
    a = ScriptArgGetFloat_1ecba0(arg0 + 0x10);
    b = ScriptArgGetFloat_1ecba0(arg0 + 0x18);
    AreaBoxSetCorner0Thunk_1e97a0(r, a, b, ScriptArgGetFloat_1ecba0(arg0 + 0x20));
    a = ScriptArgGetFloat_1ecba0(arg0 + 0x28);
    b = ScriptArgGetFloat_1ecba0(arg0 + 0x30);
    AreaBoxSetCorner1Thunk_1e9790(r, a, b, ScriptArgGetFloat_1ecba0(arg0 + 0x38));
    AreaBoxCalcThunk_1e9650(r);
    return 1;
}
