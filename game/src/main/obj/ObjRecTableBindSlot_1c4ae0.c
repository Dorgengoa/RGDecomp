/* rgp:protos */
#define RGP_SELF_ObjRecTableBindSlot_1c4ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/
extern s32 D_0047E268;

s32 ObjRecTableBindSlot_1c4ae0(void *arg0, s32 arg1, s32 arg2, s32 *arg3)
{
    s32 *p;
    s32 i;
    s32 b;

    if (arg1 < 0) {
        for (i = 0; i < *(s32 *)((u8 *)arg0 + 0x1810); i++) {
            p = ((s32 *)ObjRecTableGet_1c3fe0(arg0, i));
            if (p != NULL) {
                b = *p == 0;
                if (b) {
                    break;
                }
            }
        }
        return -1;
    }
    p = ((s32 *)ObjRecTableGet_1c3fe0(arg0, arg1));
    if (p == NULL) {
        return -1;
    }
    if (arg3 == NULL) {
        arg3 = &D_0047E268;
    }
    if (ObjRecBind_1c4760(p, arg2, arg3) < 0) {
        return -1;
    }
    return arg1;
}
