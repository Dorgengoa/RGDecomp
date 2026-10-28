/* rgp:protos */
#define RGP_SELF_EquipSlotGetAbilityWeaponSlot_3a06e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_003a06e0 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
} Obj4_FUN_003a06e0;

/*rgp*/

s32 EquipSlotGetAbilityWeaponSlot_3a06e0(Obj4_FUN_003a06e0 *o)
{
    return AbilityDataGetWeaponSlot_3f5d50(o->m04);
}
