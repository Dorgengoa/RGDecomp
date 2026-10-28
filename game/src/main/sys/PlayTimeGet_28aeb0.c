/* rgp:protos */
#define RGP_SELF_PlayTimeGet_28aeb0 1
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
struct Obj1;
struct Obj2;
struct Obj3;
struct Obj4;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    s32 m00;
};

struct Obj3 {
    s32 m00;
};

struct Obj4 {
    u8 pad000[0xC];
    s32 m0C;
};

struct Obj4 *PlayTimeGet_28aeb0(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2, struct Obj3 *p3)
{
    struct Obj4 *r0;
    s32 t0;
    s32 r1;

    p0->m00 = 0;
    p1->m00 = 0;
    p2->m00 = 0;
    p3->m00 = 0;
    r0 = GetGameData_1fede0();
    if (r0 != 0) {
        t0 = r0->m0C;
        r1 = PlayTimeSplitFromHandle_3d6220(t0, p0, p1, p2, p3);
        return (struct Obj4 *)r1;
    }
}
