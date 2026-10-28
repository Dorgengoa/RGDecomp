/* rgp:protos */
#define RGP_SELF_MapObjRequestLoad_1e0a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s16 m14;
    s16 m16;
};

s32 MapObjRequestLoad_1e0a10(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 rv2;
    s32 r1;

    MapObjRelease_1e0a90(p0);
    rv2 = 1;
    if (p1 == 0) {
        rv2 = 0;
    } else {
        r1 = ((short)LoadHandleRequestFile_1ccbb0(p0, p1));
        p0->m10 = p2;
        p0->m14 = p3;
        p0->m16 = 1;
        rv2 = 1;
    }
    return rv2;
}
