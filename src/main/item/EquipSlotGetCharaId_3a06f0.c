#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_003a06f0 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
} Obj4_FUN_003a06f0;

extern s32 AbilityDataGetCharaId_3f5d80(s32);

s32 EquipSlotGetCharaId_3a06f0(Obj4_FUN_003a06f0 *o)
{
    return AbilityDataGetCharaId_3f5d80(o->m04);
}
