#include "types.h"

struct Obj0 { s32 m00; };

extern s32 MapFindAreaBlockBoxAtPos_1e3ac0(s32, s32, s32 *, s32, s32, f32);
extern s32 MapDataGetType_1e7c00(s32);

s32 MapLocateAtPos_1e3a60(s32 p0, s32 p1, struct Obj0 *p2, s32 p3, s32 p4, f32 fa0)
{
    s32 v2C;
    s32 rv;
    s32 r1;

    rv = MapFindAreaBlockBoxAtPos_1e3ac0(p0, p1, &v2C, p3, p4, fa0);
    if (p2 != 0) {
        if (v2C != 0) {
            r1 = MapDataGetType_1e7c00(v2C);
            rv = r1;
            if (r1 == 4) {
                p2->m00 = v2C;
                goto done;
            }
        }
        p2->m00 = 0;
    }
done:
    return rv;
}
