#include "types.h"

/* Null-checked chase with the condition MATERIALISED: the sltu
   before the beql is a u8 bool built from the comparison.
   Proven at AnimResGetMaterialKeyList_14bef0. */

typedef struct Sub_FUN_0014cd90 {
    u8 pad000[0x60];
    s32 val;         /* +0x60 */
} Sub_FUN_0014cd90;

typedef struct Obj_FUN_0014cd90 {
    Sub_FUN_0014cd90 *p;   /* +0x0 */
} Obj_FUN_0014cd90;

s32 ModelResGetVertexBufMaybe_14cd90(Obj_FUN_0014cd90 *o)
{
    Sub_FUN_0014cd90 *p;
    u8 live;

    p = o->p;
    live = p != 0;
    if (live != 0) {
        return p->val;
    }
    return 0;
}
