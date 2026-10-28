/* rgp:protos */
#define RGP_SELF_ObjListFindRecByName_1894d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 ObjListFindRecByName_1894d0(s32 p0, s32 p1)
{
    s32 v1C;
    struct Obj0 *r0;
    s32 t0;

    r0 = ObjListFindByName_189500(p0, p1, &v1C);
    if (r0 != 0) {
        t0 = r0->m10;
        return t0;
    }
    return 0;
}
