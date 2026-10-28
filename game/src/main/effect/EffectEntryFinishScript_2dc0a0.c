/* rgp:protos */
#define RGP_SELF_EffectEntryFinishScript_2dc0a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C];
    s16 m1C;
};

s32 EffectEntryFinishScript_2dc0a0(struct Obj0 *p0)
{
    s32 v2C;
    s32 r0;
    s16 t0;
    s32 r1;
    s32 t1;
    s32 r2;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    v2C = 0;
    t0 = p0->m1C;
    r1 = ((s32)LoaderGetData_1cd490(r0, t0, &v2C));
    t1 = v2C;
    r2 = EffectEntryLoadScript_2dbeb0(p0, r1, t1);
    return r2;
}
