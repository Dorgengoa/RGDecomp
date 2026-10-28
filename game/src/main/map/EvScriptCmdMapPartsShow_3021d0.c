/* rgp:protos */
#define RGP_SELF_EvScriptCmdMapPartsShow_3021d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EvScriptCmdMapPartsShow_3021d0(s32 pad0, u8 *arg1, s32 arg2)
{
    u8 *p;
    s32 f;

    if (arg2 != 3) {
        return 1;
    }
    p = (u8 *)EvScriptArgsFindMapObj_3026d0(arg1, arg1 + 5);
    if (p == NULL) {
        return 1;
    }
    f = ScriptArgGetInt_302d70(arg1 + 0xA) != 0;
    if (f) {
        *(u16 *)(p + 0x32) = 1;
        *(s32 *)(p + 0x3C) &= ~1;
    } else {
        *(u16 *)(p + 0x32) = 0;
        *(s32 *)(p + 0x3C) |= 1;
    }
    return 1;
}
