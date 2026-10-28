/* rgp:protos */
#define RGP_SELF_EventObjMgrSpPlayAllowedMaybe_2e79f0 1
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
    u8 pad000[0x10];
    s32 m10;
};

s32 EventObjMgrSpPlayAllowedMaybe_2e79f0(void)
{
    s32 r0;
    struct Obj0 *r1;
    s32 t0;
    s32 r2;

    r0 = EvtCurIsRunning_26abf0();
    if (r0 == 0) {
        return 1;
    }
    r1 = (struct Obj0 *)GetGameData_1fede0();
    t0 = r1->m10;
    r2 = StateFlagTest_3ccd70(t0, 0x7E4);
    return !(r2 != 0);
}
