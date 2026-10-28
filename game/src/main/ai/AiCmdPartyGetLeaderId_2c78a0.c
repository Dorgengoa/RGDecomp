/* rgp:protos */
#define RGP_SELF_AiCmdPartyGetLeaderId_2c78a0 1
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
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

s32 AiCmdPartyGetLeaderId_2c78a0(s32 p0, s32 p1)
{
    s32 rv2;
    struct Obj0 *r0;
    struct Obj1 * t0;
    s16 t1;
    s32 r1;

    rv2 = 1;
    if (p1 != 1) {
        rv2 = 0;
    } else {
        r0 = GetGameData_1fede0();
        t0 = r0->m18;
        t1 = r0->m18->m18E;
        r1 = (ScriptSlotStoreIntRef_2cc900(p0, t1), (s32)0);
        rv2 = 1;
    }
    return rv2;
}
