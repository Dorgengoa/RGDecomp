#include "types.h"

typedef unsigned __int128 u128;

struct Obj0 { u128 m00; u128 m10; };
struct Obj1 { s32 m00; u8 pad004[0x6]; u8 m0A; };

extern s32 TreasureBoxCollectCollTrisNone_3393e0(s32, s32, s32, void *);

s32 TreasureBoxPoolCollectCollTris_338a30(struct Obj1 *p0, s32 p1, s32 p2, struct Obj0 *p3)
{
    struct Obj0 v;
    s32 l4;
    s32 l3;
    s32 l2;
    s32 l1;
    s32 l0;
    s32 r5;

    l4 = p1;
    l3 = p2;
    v = *p3;
    l1 = p0->m00;
    if (l1 == 0) {
        return 0;
    }
    if ((p0->m0A & 1) == 0) {
        return 0;
    }
    l2 = 0;
    l0 = 0;
    do {
        r5 = TreasureBoxCollectCollTrisNone_3393e0(l1, l4, l3, &v);
        l4 = (l4 + (r5 * 96));
        l2 = (l2 + r5);
        l3 = (l3 - r5);
        l0 = (l0 + 1);
        l1 = (l1 + 0x80);
    } while (l0 < 0x20);
    return l2;
}
