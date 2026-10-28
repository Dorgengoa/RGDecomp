/* rgp:protos */
#define RGP_SELF_CharaIsTargetableMaybe_210280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 CharaIsTargetableMaybe_210280(void *arg0)
{
    s32 temp_3;

    temp_3 = *(s32 *)((u8 *)arg0 + 0xA44);
    if (temp_3 & 0x80000) {
        return 0;
    }
    if (temp_3 & 0x40) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0xA38) == 0) {
        switch (*(s16 *)((u8 *)arg0 + 0xA32)) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        default:
            return 0;
        }
    }
    return 1;
}
