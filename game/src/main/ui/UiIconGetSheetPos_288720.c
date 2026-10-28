/* rgp:protos */
#define RGP_SELF_UiIconGetSheetPos_288720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void UiIconGetSheetPos_288720(s32 arg0, s32 v, s16 *arg2, s16 *arg3) {
    if (arg2 == NULL || arg3 == NULL) {
        return;
    }
    switch (arg0) {
    case 3:
        if (v <= 0 || v > 5) {
            v = 1;
        }
        *arg2 = (v - 1) << 8;
        *arg3 = 0x300;
        break;
    case 2:
        if (v <= 0 || v > 5) {
            v = 1;
        }
        *arg2 = (v - 1) << 8;
        *arg3 = 0;
        break;
    case 1:
        if (v <= 0 || v > 9) {
            v = 1;
        }
        *arg2 = ((v - 1) % 4) << 8;
        *arg3 = ((v - 1) / 4 + 1) << 8;
        break;
    default:
        *arg2 = 0;
        *arg3 = 0;
        break;
    }
}
