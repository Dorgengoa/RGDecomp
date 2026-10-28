/* rgp:protos */
#define RGP_SELF_ItemGetBuyPrice_3d4340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003d4340 {
    u8 pad000[0x1A];
    s16 val;         /* +0x1A */
} Sub_FUN_003d4340;

typedef struct Obj_FUN_003d4340 {
    u8 pad000[0x10];
    Sub_FUN_003d4340 *p;         /* +0x10 */
} Obj_FUN_003d4340;

s16 ItemGetBuyPrice_3d4340(Obj_FUN_003d4340 *o)
{
    Sub_FUN_003d4340 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
