/* rgp:protos */
#define RGP_SELF_WorldDataRequestKind_3f0960 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct Obj1 { s16 m00; s16 m02; s16 m04; };
struct Obj0 { u8 pad000[0x28]; struct Obj1 *m28; };

s32 WorldDataRequestKind_3f0960(struct Obj0 *p0, s32 p1)
{
    struct Obj1 *t0;

    t0 = p0->m28;
    if (t0 == 0) {
        return 0;
    }
    if (t0->m02 == 2) {
        return 0;
    }
    t0->m00 = p1;
    t0->m04 = 1;
    t0->m02 = 2;
    return 1;
}
