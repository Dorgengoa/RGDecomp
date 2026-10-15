#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003d4320 {
    u8 pad000[0x1C];
    s16 val;         /* +0x1C */
} Sub_FUN_003d4320;

typedef struct Obj_FUN_003d4320 {
    u8 pad000[0x10];
    Sub_FUN_003d4320 *p;         /* +0x10 */
} Obj_FUN_003d4320;

s16 ItemGetSellPrice_3d4320(Obj_FUN_003d4320 *o)
{
    Sub_FUN_003d4320 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
