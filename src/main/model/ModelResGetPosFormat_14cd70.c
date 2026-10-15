#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0x20 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014cd70 {
    u8 pad000[0x10];
    u8 val;         /* +0x10 */
} Sub_FUN_0014cd70;

typedef struct Obj_FUN_0014cd70 {
    Sub_FUN_0014cd70 *p;         /* +0x0 */
} Obj_FUN_0014cd70;

s32 ModelResGetPosFormat_14cd70(Obj_FUN_0014cd70 *o)
{
    Sub_FUN_0014cd70 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0x20;
}
