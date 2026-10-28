/* rgp:protos */
#define RGP_SELF_EvCmdRecordGetStateParamMaybe_25f1c0 1
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
    u8 pad000[0x24];
    s32 m24;
};

s32 EvCmdRecordGetStateParamMaybe_25f1c0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = GetGameData_1fede0();
    t0 = r0->m24;
    r1 = RecordGetStateParamMaybe_430890(t0);
    if (p1 > 0) {
        r2 = (ScriptSetRefInt_26a1e0(p0, r1), (s32)0);
    }
    return 1;
}
