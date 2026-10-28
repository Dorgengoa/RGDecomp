/* rgp:protos */
#define RGP_SELF_StatusEntryTryExpire_3a15c0 1
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
    u8 m00;
};

s32 StatusEntryTryExpire_3a15c0(s32 p0, struct Obj0 *p1)
{
    s32 rv4;
    u8 t0;
    s32 rv3;
    s32 r0;
    s32 rv2;
    s32 r1;

    rv4 = rv3;
    if (p1 == 0) {
        rv4 = 0;
    } else {
        t0 = p1->m00;
        rv3 = rv2;
        if (t0 == 0) {
            rv3 = 0;
        } else {
            r0 = StatusEntryIsRunning_3a6190(p1);
            rv2 = 1;
            if (r0 == 0) {
                rv2 = 0;
            } else {
                r1 = StatusEntryExpire_3a5f40(p1, 0);
                rv2 = 1;
            }
            rv3 = rv2;
        }
        rv4 = rv3;
    }
    return rv4;
}
