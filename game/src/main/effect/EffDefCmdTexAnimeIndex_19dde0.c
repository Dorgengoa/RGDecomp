/* rgp:protos */
#define RGP_SELF_EffDefCmdTexAnimeIndex_19dde0 1
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

struct Obj0 {
    struct Obj1 *m00;
};

struct Obj1 {
    u8 pad000[0x20];
    s32 m20;
    u8 pad024[0x30];
    s32 m54;
};

struct Obj2 {
    u8 pad000[0x10];
    u16 m10;
    u8 pad012[0x2];
    s32 m14;
};

s32 EffDefCmdTexAnimeIndex_19dde0(s32 p0, s32 p1, struct Obj0 *p2)
{
    struct Obj1 * t0;
    s32 t1;
    s32 t2;
    struct Obj2 *r0;
    s32 l1;
    s32 r2;
    s32 t3;

    t0 = p2->m00;
    t1 = p2->m00->m54;
    if (t1 == 0) {
        return 0;
    }
    t2 = p2->m00->m20;
    r0 = EffTexAnimeParamAppendStep_1981f0(t1, t2, 2, p1);
    l1 = 0;
    while (l1 < r0->m10) {
        r2 = VariantGetInt_15f780((p0 + (l1 << 3)));
        t3 = r0->m14;
        *(s16 *)((u8 *)t3 + (l1 << 1)) = r2;
        l1 = (l1 + 1);
    }
    return 1;
}
