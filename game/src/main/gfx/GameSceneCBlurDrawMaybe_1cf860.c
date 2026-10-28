/* rgp:protos */
#define RGP_SELF_GameSceneCBlurDrawMaybe_1cf860 1
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
    u8 pad000[0x58B0];
    s8 m58B0;
    s8 m58B1;
    s16 m58B2;
    s16 m58B4;
    s16 m58B6;
};

void GameSceneCBlurDrawMaybe_1cf860(struct Obj0 *p0)
{
    s8 t0;
    s16 t1;
    s8 t2;
    s16 t3;
    s16 t4;

    t0 = p0->m58B0;
    if (t0 != 0) {
        t1 = p0->m58B2;
        t2 = p0->m58B1;
        t3 = p0->m58B4;
        t4 = p0->m58B6;
        CBlurDrawMaybe_1784e0((struct Obj0 *)((u8 *)p0 + 0x58C0), (struct Obj0 *)((u8 *)p0 + 0x58A0), t1, t2, t3, t4);
    }
}
