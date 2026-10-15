#include "types.h"
struct Obj0 { u8 pad000[0x180]; s32 m180; u8 pad184[0x4]; s16 m188; };
s32 EvDoorObjGetRefList_303ff0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t2;
    t0 = p0->m180;
    if (t0 == 0) {
        return 0;
    }
    if (p1 >= 0) {
        if (p0->m188 > p1) {
            goto ok;
        }
    }
    return 0;
ok:
    return (t0 + (p1 * 12));
}
