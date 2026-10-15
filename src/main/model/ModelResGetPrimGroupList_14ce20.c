#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014ce20 {
    u8 pad000[0x74];
    s32 val;         /* +0x74 */
} Sub_FUN_0014ce20;

typedef struct Obj_FUN_0014ce20 {
    Sub_FUN_0014ce20 *p;         /* +0x0 */
} Obj_FUN_0014ce20;

s32 ModelResGetPrimGroupList_14ce20(Obj_FUN_0014ce20 *o)
{
    Sub_FUN_0014ce20 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
