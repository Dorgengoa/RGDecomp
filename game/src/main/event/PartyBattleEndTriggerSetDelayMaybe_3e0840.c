/* rgp:protos */
#define RGP_SELF_PartyBattleEndTriggerSetDelayMaybe_3e0840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483990;
extern s32 D_004839B4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
};

s32 PartyBattleEndTriggerSetDelayMaybe_3e0840(s32 p0, s32 p1)
{
    struct Obj0 * t0;
    s32 rv4;
    s32 t1;
    s32 r0;
    s32 rv3;
    s32 rv2;
    struct Obj0 * t2;
    s32 r1;

    t0 = D_00483990;
    rv4 = rv3;
    if (t0 == 0) {
        rv4 = 0;
    } else {
        t1 = D_00483990->m20;
        r0 = CharaSysGetEncounterIdMaybe_3a36d0(t1);
        rv3 = 1;
        if (r0 >= 0) {
            rv3 = 0;
        } else {
            rv2 = r0;
            if (p1 != 0) {
                t2 = D_00483990;
                r1 = (SkillLockClearResetSpot_3eb6c0(t2, 1), (s32)0);
                D_004839B4 = p0;
                rv2 = r1;
            } else {
                D_004839B4 = p0;
                rv2 = r0;
            }
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
