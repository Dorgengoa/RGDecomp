#include "types.h"

typedef struct Obj003c1bd0 {
    u8 pad0[0x196];
    s16 arr196[7];
} Obj003c1bd0;

s32 PartyIsInReserve_3c1bd0(Obj003c1bd0 *arg0, s32 val)
{
    s32 i;
    s32 r;

    if (val < 0) {
        r = -1;
    } else {
        for (i = 0; i < 7; i++) {
            if (arg0->arr196[i] == val) {
                r = i;
                goto out;
            }
        }
        r = -1;
    }
out:
    return r >= 0;
}
