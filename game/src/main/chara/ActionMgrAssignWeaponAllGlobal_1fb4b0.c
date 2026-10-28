/* rgp:protos */
#define RGP_SELF_ActionMgrAssignWeaponAllGlobal_1fb4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004B8680[];

/*rgp*/

s32 ActionMgrAssignWeaponAllGlobal_1fb4b0(s32 a4)
{
    return ActionMgrAssignWeaponAll_233650(D_004B8680, a4);
}
