#include "types.h"

extern s32 TreasureBoxIsInReach_33add0(s32);

struct Obj0 {
    s32 m00;
};

s32 TreasureBoxPoolCollectInReach_3391d0(struct Obj0 *p0, s32 *p1, s32 p2)
{
    s32 l2;
    s32 l1;
    s32 l0;
    s32 r3;

    if (p1 == 0) {
        return 0;
    }
    if (p2 <= 0) {
        return 0;
    }
    l1 = p0->m00;
    if (l1 == 0) {
        return 0;
    }
    l2 = 0;
    l0 = 0;
    while (l0 < 0x20) {
        r3 = TreasureBoxIsInReach_33add0(l1);
        if (r3 != 0) {
            p1[l2] = l1;
            l2 = (l2 + 1);
        }
        if (l2 < p2) {
            l0 = (l0 + 1);
            l1 = (l1 + 0x80);
        } else {
            break;
        }
    }
    return l2;
}
