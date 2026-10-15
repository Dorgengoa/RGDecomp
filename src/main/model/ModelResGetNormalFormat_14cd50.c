#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0x20 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014cd50 {
    u8 pad000[0x11];
    u8 val;         /* +0x11 */
} Sub_FUN_0014cd50;

typedef struct Obj_FUN_0014cd50 {
    Sub_FUN_0014cd50 *p;         /* +0x0 */
} Obj_FUN_0014cd50;

s32 ModelResGetNormalFormat_14cd50(Obj_FUN_0014cd50 *o)
{
    Sub_FUN_0014cd50 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0x20;
}
