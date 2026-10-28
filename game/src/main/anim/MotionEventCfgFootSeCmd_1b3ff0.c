/* rgp:protos */
#define RGP_SELF_MotionEventCfgFootSeCmd_1b3ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub001b3ff0 {
    u8 pad000[0x28];
    s32 unk28;
    s32 unk2C;
} Sub001b3ff0;

typedef struct T001b3ff0 {
    u8 pad000[0x48];
    Sub001b3ff0 *unk48;
} T001b3ff0;

/*rgp*/

s32 MotionEventCfgFootSeCmd_1b3ff0(s32 arg0, s32 arg1, T001b3ff0 **arg2)
{
    T001b3ff0 *temp16;

    temp16 = *arg2;
    if (temp16->unk48 == 0) {
        return 0;
    }
    temp16->unk48->unk28 = VariantGetInt_15f780(arg0);
    if (arg1 >= 2) {
        temp16->unk48->unk2C = VariantGetInt_15f780(arg0 + 8);
    }
    return 1;
}
