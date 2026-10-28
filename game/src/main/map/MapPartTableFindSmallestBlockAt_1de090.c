/* rgp:protos */
#define RGP_SELF_MapPartTableFindSmallestBlockAt_1de090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj0_001DE090 {
    f32 x;
    f32 y;
    f32 z;
} Obj0_001DE090;

typedef struct Obj1_001DE090 {
    u8 pad0[0x4];
    s32 *list;
    s16 count;
    u8 padA[2];
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
} Obj1_001DE090;

/*rgp*/
/*rgp*/
extern f32 D_0047D1EC;

s32 MapPartTableFindSmallestBlockAt_1de090(Obj1_001DE090 *arg0, Obj0_001DE090 *arg1, f32 r)
{
    s32 best;
    s32 *p;
    s32 i;
    f32 bestd;
    f32 d;

    p = arg0->list;
    if (p == NULL || arg0->count <= 0) {
        return 0;
    }
    if (arg1->x + r < arg0->maxX) {
        return 0;
    }
    if (arg1->y + r < arg0->maxY) {
        return 0;
    }
    if (arg1->z + r < arg0->maxZ) {
        return 0;
    }
    if (!(arg1->x - r <= arg0->minX)) {
        return 0;
    }
    if (!(arg1->y - r <= arg0->minY)) {
        return 0;
    }
    if (!(arg1->z - r <= arg0->minZ)) {
        return 0;
    }
    best = 0;
    bestd = D_0047D1EC;
    for (i = 0; i < arg0->count; i++, p++) {
        if (MapBlockBoundsContains_1dfca0(*p, arg1, r) != 0) {
            d = MapBlockGetBoxVolume_1dfe80(*p);
            if (!(bestd <= d)) {
                best = *p;
                bestd = d;
            }
        }
    }
    return best;
}
