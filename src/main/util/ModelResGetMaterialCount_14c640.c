#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014c640 {
    u8 pad000[0x2C];
    s32 val;         /* +0x2C */
} Sub_FUN_0014c640;

typedef struct Obj_FUN_0014c640 {
    Sub_FUN_0014c640 *p;         /* +0x0 */
} Obj_FUN_0014c640;

s32 ModelResGetMaterialCount_14c640(Obj_FUN_0014c640 *o)
{
    Sub_FUN_0014c640 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
