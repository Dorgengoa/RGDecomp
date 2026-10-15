#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003d0d60 {
    u8 pad000[0xC];
    s32 val;         /* +0xC */
} Sub_FUN_003d0d60;

typedef struct Obj_FUN_003d0d60 {
    u8 pad000[0x10];
    Sub_FUN_003d0d60 *p;         /* +0x10 */
} Obj_FUN_003d0d60;

s32 ItemGetNamePtr_3d0d60(Obj_FUN_003d0d60 *o)
{
    Sub_FUN_003d0d60 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
