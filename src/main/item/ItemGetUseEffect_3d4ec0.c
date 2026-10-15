#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003d4ec0 {
    u8 pad000[0x24];
    s32 val;         /* +0x24 */
} Sub_FUN_003d4ec0;

typedef struct Obj_FUN_003d4ec0 {
    u8 pad000[0x10];
    Sub_FUN_003d4ec0 *p;         /* +0x10 */
} Obj_FUN_003d4ec0;

s32 ItemGetUseEffect_3d4ec0(Obj_FUN_003d4ec0 *o)
{
    Sub_FUN_003d4ec0 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
