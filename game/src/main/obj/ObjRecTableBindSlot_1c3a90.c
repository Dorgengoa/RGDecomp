/* rgp:protos */
#define RGP_SELF_ObjRecTableBindSlot_1c3a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/
extern s32 D_0047E260;

s32 ObjRecTableBindSlot_1c3a90(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 i;
    s32 *p;
    s32 z;

    if (arg1 < 0) {
        for (i = 0; i < *(s32 *)(arg0 + 0x3F7C); i++) {
            p = ((s32 *)ObjRecTableGet_1c3b80(arg0, i));
            if (p != NULL) {
                z = *p == 0;
                if (z) {
                    arg1 = i;
                    break;
                }
            }
        }
        if (arg1 < 0) {
            return -1;
        }
    }
    p = ((s32 *)ObjRecTableGet_1c3b80(arg0, arg1));
    if (p == NULL) {
        return -1;
    }
    if (arg3 == NULL) {
        arg3 = (u8 *)&D_0047E260;
    }
    if (ObjRecBind_1c4ef0(p, arg2, arg3, 0) != 0) {
        return arg1;
    }
    return -1;
}
