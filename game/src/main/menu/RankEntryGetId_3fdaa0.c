/* rgp:protos */
#define RGP_SELF_RankEntryGetId_3fdaa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003fdaa0 {
    s16 val;         /* +0x0 */
} Sub_FUN_003fdaa0;

typedef struct Obj_FUN_003fdaa0 {
    Sub_FUN_003fdaa0 *p;         /* +0x0 */
} Obj_FUN_003fdaa0;

s16 RankEntryGetId_3fdaa0(Obj_FUN_003fdaa0 *o)
{
    Sub_FUN_003fdaa0 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
