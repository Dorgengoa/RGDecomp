/* rgp:protos */
#define RGP_SELF_UnitGetDefAttackIdMaybe_3bd120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003bd120 {
    u8 pad000[0x74];
    s32 val;         /* +0x74 */
} Sub_FUN_003bd120;

typedef struct Obj_FUN_003bd120 {
    u8 pad000[0x234];
    Sub_FUN_003bd120 *p;         /* +0x234 */
} Obj_FUN_003bd120;

s32 UnitGetDefAttackIdMaybe_3bd120(Obj_FUN_003bd120 *o)
{
    Sub_FUN_003bd120 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
