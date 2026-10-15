#include "types.h"
#pragma opt_propagation off
typedef struct {
    u8 pad[0x18];
    s32 f18;
} Mgr;

extern s16 D_0047FF50;
extern s32 D_00483564;
extern "C" {
Mgr *GetGameData_1fede0(void);
s32 InvGetCageItem_3c8040(s32, s16);
s16 InsectRecSlotCountItems_3cfb80(s32);
}

extern "C" s32 InsectMenuSkipFullCageMaybe_395920(u8 *arg0) {
    s32 cur;
    s32 r;
    bool bad;
    s32 b1;

    if (*(s16 *)(arg0 + 8) == 0) {
        *(s16 *)(arg0 + 0x10) = D_00483564;
    }
    cur = *(s16 *)(arg0 + 0x10);
    for (;;) {
        r = InvGetCageItem_3c8040(GetGameData_1fede0()->f18, cur);
        if (!r || (D_0047FF50 = InsectRecSlotCountItems_3cfb80(r)) >= 5) {
            bad = true;
        } else {
            break;
        }
        if (bad) {
            if (*(s16 *)(arg0 + 0x10) < D_00483564) {
                cur = (s16)(cur - 1);
                if (cur < 0) {
                    cur = (s16)D_00483564;
                }
            } else {
                cur = (s16)(cur + 1);
                if (cur > 2) {
                    cur = (s16)D_00483564;
                }
            }
        }
    }
    *(s16 *)(arg0 + 0x10) = cur;
    D_00483564 = (s16)cur;
    return 1;
}
