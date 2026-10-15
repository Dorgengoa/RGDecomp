#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014ce60 {
    u8 pad000[0x60];
    s32 val;         /* +0x60 */
} Sub_FUN_0014ce60;

typedef struct Obj_FUN_0014ce60 {
    Sub_FUN_0014ce60 *p;         /* +0x0 */
} Obj_FUN_0014ce60;

s32 ModelResGetVertexBufMaybe_14ce60(Obj_FUN_0014ce60 *o)
{
    Sub_FUN_0014ce60 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
