/* rgp:protos */
#define RGP_SELF_CharaWeaponTrailSetupByName_21f770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaWeaponTrailSetupByName_21f770(s32 p0, s32 p1, s32 p2, s32 p3, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)ActCfgTableFindLocusByName_2226d0(p0, p2));
    if (r0 != 0) {
        r1 = CharaWeaponTrailSetup_22f500(r0, p1, p3, fa0, fa1, fa2, fa3);
        return (r1 & 0xFF);
    }
    return -1;
}
