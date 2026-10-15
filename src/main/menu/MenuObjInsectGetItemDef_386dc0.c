#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_00386dc0 {
    u8 pad000[0x10];
    s32 val;         /* +0x10 */
} Sub_FUN_00386dc0;

typedef struct Obj_FUN_00386dc0 {
    u8 pad000[0x96C];
    Sub_FUN_00386dc0 *p;         /* +0x96C */
} Obj_FUN_00386dc0;

s32 MenuObjInsectGetItemDef_386dc0(Obj_FUN_00386dc0 *o)
{
    Sub_FUN_00386dc0 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
