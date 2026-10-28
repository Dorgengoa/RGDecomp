/* rgp:protos */
#define RGP_SELF_ActionMgrRemoveWeaponAllGlobal_1fb4a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004B8680[];

/*rgp*/

s32 ActionMgrRemoveWeaponAllGlobal_1fb4a0(s32 a4)
{
    return ActionMgrRemoveWeaponAll_2335f0(D_004B8680, a4);
}
