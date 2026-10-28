/* rgp:protos */
#define RGP_SELF_CameraModeSetTrackIndexCur_309e90 1
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

struct Obj0 {
    u8 pad000[0x4344];
    s32 m4344;
};

struct Obj1 {
    u8 pad000[0x270];
    s32 m270;
};

struct Obj1 *CameraModeSetTrackIndexCur_309e90(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;
    struct Obj1 *r1;

    r0 = GetCurrentScene_1f5be0();
    t0 = r0->m4344;
    r1 = ObjRecGetLiveObject_1c3bc0(r0, t0);
    r1->m270 = p0;
    return r1;
}
