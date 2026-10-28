/* rgp:protos */
#define RGP_SELF_RankEntryGetName_3fda80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003fda80 {
    u8 pad000[0xC];
    s32 val;         /* +0xC */
} Sub_FUN_003fda80;

typedef struct Obj_FUN_003fda80 {
    Sub_FUN_003fda80 *p;         /* +0x0 */
} Obj_FUN_003fda80;

s32 RankEntryGetName_3fda80(Obj_FUN_003fda80 *o)
{
    Sub_FUN_003fda80 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
