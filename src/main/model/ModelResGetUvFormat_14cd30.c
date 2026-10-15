#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0x20 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014cd30 {
    u8 pad000[0x12];
    u8 val;         /* +0x12 */
} Sub_FUN_0014cd30;

typedef struct Obj_FUN_0014cd30 {
    Sub_FUN_0014cd30 *p;         /* +0x0 */
} Obj_FUN_0014cd30;

s32 ModelResGetUvFormat_14cd30(Obj_FUN_0014cd30 *o)
{
    Sub_FUN_0014cd30 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0x20;
}
