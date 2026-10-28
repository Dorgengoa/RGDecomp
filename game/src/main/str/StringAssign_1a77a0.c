/* rgp:protos */
#define RGP_SELF_StringAssign_1a77a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct V3 {
    f32 x;
    f32 y;
    f32 z;
} V3;

void *StringAssign_1a77a0(void *arg0, void *arg1) {
    s32 temp_3;
    u64 var_6;

    temp_3 = (*(s32 *)((u8 *)arg0 + 0) & 1) != 0;
    if ((temp_3 == 0) && !(*(s32 *)((u8 *)arg1 + 0) & 1)) {
        *(V3 *)arg0 = *(V3 *)arg1;
        return arg0;
    }
    {
        if (temp_3 != 0) {
            var_6 = (u64)*(s32 *)((u8 *)arg0 + 4);
        } else {
            var_6 = (u64)((s64)(u8)(*(u8 *)arg0) << 0x38) >> 0x39;
        }
        return StringReplaceWithStr_1a7820(arg0, 0, (int)(var_6), arg1);
    }
}
