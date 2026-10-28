/* rgp:protos */
#define RGP_SELF_ObjTypeMonographCtor_372d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472000[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *ObjTypeMonographCtor_372d20(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)EvObjCtor_2f9f00(p0));
    p0->mDC = D_00472000;
    r1 = (ObjTypeMonographReset_372cd0(p0), (s32)0);
    return p0;
}
