/* rgp:protos */
#define RGP_SELF_CharaSysStateGetChallengeKindMaybe_3a3800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries -1 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003a3800 {
    u8 pad000[0x2C];
    s16 val;         /* +0x2C */
} Sub_FUN_003a3800;

typedef struct Obj_FUN_003a3800 {
    u8 pad000[0x238];
    Sub_FUN_003a3800 *p;         /* +0x238 */
} Obj_FUN_003a3800;

s32 CharaSysStateGetChallengeKindMaybe_3a3800(Obj_FUN_003a3800 *o)
{
    Sub_FUN_003a3800 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
