/* rgp:protos */
#define RGP_SELF_ActionMgrAssignWeaponAll_233650 1
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

int ActionMgrAssignWeaponAll_233650(s32 p0, s32 p1)
{ int rgp_v0 = 0;
    s32 r0;
    s32 l1;
    s32 r3;

    r0 = (rgp_v0 = DListGetHead_42ea60((p0 + 0x20)));
    l1 = r0;
    while (l1 != 0) {
        CharaAssignWeapon_214620((l1 + 0x10), p1);
        r3 = (rgp_v0 = DListGetNext_42eb30(l1));
        l1 = r3;
    }
return rgp_v0; }
