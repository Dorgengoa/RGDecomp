/* rgp:protos */
#define RGP_SELF_ModelResCalcPrimCountMaybe_15c780 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on

#include "types.h"

typedef struct S0015c780 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x128 - 0x10];
    s32 unk128;
} S0015c780;

s32 ModelResCalcPrimCountMaybe_15c780(S0015c780 *arg0, s32 arg1, s32 *arg2)
{
    s32 v;

    *arg2 = 0;
    if ((arg1 & 0xF0) == 0x10) {
        v = (arg0->unkC - 4) / 6;
        switch (arg1) {
        case 17:
            v = v / 2 * 2 - 2;
            break;
        case 19:
            v = v / 4 * 4 - 4;
            break;
        }
    } else {
        if (arg0->unk128 > 0) {
            v = (arg0->unkC - 4) / 6;
        } else {
            v = (arg0->unkC - 4) / 4;
        }
        switch (arg1) {
        case 4:
            v = v / 2 * 2 - 4;
            *arg2 = 2;
            break;
        case 3:
            v = (1 - v / 3) * -3;
            break;
        }
    }
    return v;
}
