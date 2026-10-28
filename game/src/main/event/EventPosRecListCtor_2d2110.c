/* rgp:protos */
#define RGP_SELF_EventPosRecListCtor_2d2110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471608[];
extern u8 D_00471618[];
extern u8 D_00471628[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    void *m0C;
};

struct Obj0 *EventPosRecListCtor_2d2110(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = (DListInit_42eae0(p0), (s32)0);
    p0->m0C = D_00471608;
    r1 = (DListInit_42eae0(p0), (s32)0);
    p0->m0C = D_00471618;
    r2 = (DListInit_42eae0(p0), (s32)0);
    p0->m0C = D_00471628;
    r3 = (DListInit_42eae0(p0), (s32)0);
    return p0;
}
