#include "types.h"

typedef struct E {
    u8 pad0[3];
    u8 lo4 : 4;
    u8 flag : 1;
    u8 hi3 : 3;
    s16 key;
} E;

void *RecTableBinSearch_407bb0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 lo;
    s32 hi;
    s32 mid;
    s32 f;
    E *e;
    s32 k;
    u8 b;

    lo = 0;
    hi = arg0[1] - 1;
    while (lo <= hi) {
        mid = lo + (hi - lo + 1) / 2;
        e = (E *)(*(u8 **)(arg0 + 4) + mid * 6);
        b = e->flag;
        k = e->key;
        f = b != 0;
        if (k == arg1) {
            if ((u8)f == (u8)arg2) {
                return e;
            }
            if ((f == 0) && (arg2 != 0)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } else if (k < arg1) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return NULL;
}
