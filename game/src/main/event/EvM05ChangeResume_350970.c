/* rgp:protos */
#define RGP_SELF_EvM05ChangeResume_350970 1
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
struct Obj1;

struct Obj0 {
    u8 pad000[0xE8];
    s32 mE8;
    s32 mEC;
    u8 pad0F0[0x4C];
    struct Obj1 *m13C;
};

struct Obj1 {
    u8 pad000[0x6C];
    s32 m6C;
};

void EvM05ChangeResume_350970(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 t1;
    s32 r0;
    s32 rv3;
    struct Obj1 * t2;
    s32 t3;
    s32 r1;
    s32 r2;
    s32 t4;
    s32 l5;
    s32 l4;
    s32 r6;

    t0 = p0->m13C;
    if (t0 != 0) {
        t1 = p0->m13C->m6C;
        if (t1 != 0) {
            r0 = EvM05ChangeGetMotionName_352030(p0);
            rv3 = 0;
            if (r0 != 0) {
                t2 = p0->m13C;
                t3 = p0->m13C->m6C;
                r1 = EvM05ChangeGetMotionName_352030(p0);
                r2 = ModelObjPlayMotionByName_1867a0(t3, r1, 4);
                rv3 = r2;
            }
        }
    }
    l4 = 0;
    l5 = p0->mE8;
    while (l4 < p0->mEC) {
        r6 = (EvTargetMapObjEnable_352510(l5), (s32)0);
        l4 = (l4 + 1);
        l5 = (l5 + 0x140);
    }
}
