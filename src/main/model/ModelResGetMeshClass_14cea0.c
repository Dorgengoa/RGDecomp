#include "types.h"

/* Null-checked chase with the condition MATERIALISED: the sltu
   before the beql is a u8 bool built from the comparison.
   Proven at AnimResGetMaterialKeyList_14bef0. */

typedef struct Sub_FUN_0014cea0 {
    u8 pad000[0x68];
    s32 val;         /* +0x68 */
} Sub_FUN_0014cea0;

typedef struct Obj_FUN_0014cea0 {
    Sub_FUN_0014cea0 *p;   /* +0x0 */
} Obj_FUN_0014cea0;

s32 ModelResGetMeshClass_14cea0(Obj_FUN_0014cea0 *o)
{
    Sub_FUN_0014cea0 *p;
    u8 live;

    p = o->p;
    live = p != 0;
    if (live != 0) {
        return p->val;
    }
    return 0;
}
