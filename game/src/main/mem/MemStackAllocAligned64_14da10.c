/* rgp:protos */
#define RGP_SELF_MemStackAllocAligned64_14da10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x20];
    s32 unk20;
    u8 pad24[0x4];
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x4];
    s32 unk34;
} T14da10_arg0;

s32 MemStackAllocAligned64_14da10(T14da10_arg0 *arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_5;
    s32 var_3;

    if (arg0->unk20 == 0) {
        temp_3_2 = (arg0->unk28 + (arg0->unk2C * 0x10)) & 0x3F;
        if (temp_3_2 != 0) {
            temp_2 = 0x40 - temp_3_2;
            var_3 = temp_2 >> 4;
            if (temp_2 < 0) {
                var_3 = (temp_2 + 0xF) >> 4;
            }
            arg0->unk2C = arg0->unk2C + var_3;
        }
        if (arg0->unk2C >= arg0->unk34) {
            arg0->unk2C = arg0->unk34;
        }
    }
    if (arg0->unk20 != 0) {
        return 0;
    }
    if (arg1 <= 0) {
        return 0;
    }
    temp_3 = arg0->unk2C;
    arg1 = (s32)((u32)temp_3 + arg1);
    if (arg0->unk34 < arg1) {
        return 0;
    }
    temp_2 = arg0->unk28 + (temp_3 * 0x10);
    arg0->unk2C = arg1;
    return temp_2;
}
