/* rgp:protos */
#define RGP_SELF_TexSetClutIndex_15a5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    __extension__ unsigned long long lo:37;
    unsigned long long f:14;
    unsigned long long hi:13;
} __attribute__((aligned(8))) Bf38;

typedef struct {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x2a];
    u8 unk32;
    u8 unk33;
    s16 unk34;
    u8 pad36[2];
    Bf38 unk38;
} T15a5b0_arg0;

void TexSetClutIndex_15a5b0(T15a5b0_arg0 *arg0, s32 arg1)
{
    s32 var_9;
    u8 temp_3;

    temp_3 = arg0->unk32;
    if (temp_3 > 0) {
        arg0->unk33 = arg1 % temp_3;
        var_9 = 1;
        if (arg0->unk6 == 8) {
            var_9 = 4;
        }
        arg0->unk38.f = arg0->unk34 + (arg0->unk33 * var_9);
    }
}
