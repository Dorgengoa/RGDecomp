/* rgp:protos */
#define RGP_SELF_EquipSlotGetAbilityKind0Rec_3a0780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_003a0780 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
} Obj4_FUN_003a0780;

/*rgp*/

s32 EquipSlotGetAbilityKind0Rec_3a0780(Obj4_FUN_003a0780 *o)
{
    return AbilityDataGetKind0Rec_3f5db0(o->m04);
}
