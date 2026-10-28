/* rgp:protos */
#define RGP_SELF_ObjGetNthAttachPointPos_1ade20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/

void *ObjGetNthAttachPointPos_1ade20(void *arg0, s32 arg1, s32 arg2, u128 *arg3) {
    s32 temp_2;
    s32 var_7;
    s32 var_8;
    u128 *out;
    u8 *var_16;

    out = (u128 *)(u32)arg3;
    *out = *(u128 *)((u8 *)arg0 + 0x180);
    var_16 = *(u8 **)((u8 *)arg0 + 0x210);
    if (var_16 == NULL) {
        return NULL;
    }
    var_8 = -1;
    for (var_7 = 0; var_7 < *(s32 *)((u8 *)arg0 + 0x20C); var_7++, var_16 += 0x20) {
        if (*(s32 *)(var_16 + 8) == arg1) {
            var_8 += 1;
        }
        if (var_8 == arg2) {
            temp_2 = ((s32)ModelGetFrame_1511f0(arg0, *(s32 *)(var_16 + 0)));
            if (temp_2 != 0) {
                FrameGetWorldPos_148f30(temp_2, out);
            }
            return var_16;
        }
    }
    return 0;
}
