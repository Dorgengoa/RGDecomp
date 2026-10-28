/* rgp:protos */
#define RGP_SELF_EventPathFindSegment_2e4420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    u8 pad000[0x8];
    s32 m08;
    s16 m0C;
    s16 m0E;
};

s32 EventPathFindSegment_2e4420(struct Obj1 *p0, s32 p1, struct Obj0 *p2)
{
    s32 base;
    s32 acc;
    s32 i;
    s32 e;
    s32 r7;
    s32 r8;

    if (p2 != 0) {
        p2->m00 = 0;
    }
    base = p0->m08;
    if (base == 0) {
        return 0;
    }
    if (p1 >= p0->m0E) {
        e = (base + (p0->m0C << 3)) - 8;
        if (p2 != 0) {
            r8 = ((short)EventPathSegGetLength_2e4770(e));
            p2->m00 = p0->m0E - r8;
        }
        return e;
    }
    acc = 0;
    i = 0;
    while (i < p0->m0C) {
        r7 = ((short)EventPathSegGetLength_2e4770(base));
        acc = acc + r7;
        if (acc > p1) {
            if (p2 != 0) {
                r8 = ((short)EventPathSegGetLength_2e4770(base));
                p2->m00 = acc - r8;
            }
            return base;
        }
        i = i + 1;
        base = base + 8;
    }
    return 0;
}
