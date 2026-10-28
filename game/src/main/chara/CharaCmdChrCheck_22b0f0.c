/* rgp:protos */
#define RGP_SELF_CharaCmdChrCheck_22b0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdChrCheck_22b0f0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 t;
    s32 b;

    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    t = GetCurrentScene_1f5be0();
    b = ((s32)ObjRecGetLiveObject_1c4a90(t, ScriptArgGetInt_302d70(arg1))) != 0;
    if (b) {
        b = ((unsigned char)ObjRecHasFlags6_1c3eb0(t, 1, ScriptArgGetInt_302d70(arg1))) != 0;
    }
    return CharaCmdRunIfElseEvnt_22e480(*arg0, b & 0xFF, (u8 *)arg1 + 5, arg2 - 1);

}
