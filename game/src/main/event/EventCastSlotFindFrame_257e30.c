/* rgp:protos */
#define RGP_SELF_EventCastSlotFindFrame_257e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/

s32 EventCastSlotFindFrame_257e30(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p;
    s32 t;
    s32 ret;
    s32 r;
    if (arg1 < 0 || arg1 >= 0x20) {
        return 0;
    }
    p = arg0 + arg1 * 0x10;
    ret = 0;
    if (*(s32 *)p != 0) {
        r = ret;
    } else {
        t = *(s32 *)(p + 0xC);
        if (t == 0) {
            return ret;
        }
        r = ((s32)FrameFindByName_149ed0(ModelGetRootFrame_1511a0(t), arg2));
    }
    return r;
}
