/* rgp:protos */
#define RGP_SELF_MemStackGetStats_14d0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node0014D0E0 Node0014D0E0;

struct Node0014D0E0 {
    Node0014D0E0 *unk0;
    u8 pad4[8 - 4];
    s32 unk8;
};

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0x18 - 0x14];
    Node0014D0E0 *unk18;
} Obj0014D0E0;

void MemStackGetStats_14d0e0(Obj0014D0E0 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 temp_3;
    s32 var_9;
    Node0014D0E0 *var_10;

    var_10 = arg0->unk18;
    *arg1 = 0;
    *arg3 = 0;
    *arg4 = 0;
    *arg2 = 0;
    while (var_10->unk0 != NULL) {
        *arg3 += 1;
        temp_3 = (s32)((u8 *)var_10->unk0 - ((u8 *)var_10 + (var_10->unk8 * 0x10)));
        var_9 = temp_3 >> 4;
        if (temp_3 < 0) {
            var_9 = (temp_3 + 0xF) >> 4;
        }
        if (var_9 != 0) {
            *arg1 += var_9;
            *arg4 += 1;
        }
        var_10 = var_10->unk0;
    }
    *arg2 = arg0->unk10 - *arg1;
}
