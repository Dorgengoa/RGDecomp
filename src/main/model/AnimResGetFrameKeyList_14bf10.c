#include "types.h"

/* Null-checked chase with the condition MATERIALISED: the sltu
   before the beql is a u8 bool built from the comparison.
   Proven at AnimResGetMaterialKeyList_14bef0. */

typedef struct Sub_FUN_0014bf10 {
    u8 pad000[0x20];
    s32 val;         /* +0x20 */
} Sub_FUN_0014bf10;

typedef struct Obj_FUN_0014bf10 {
    Sub_FUN_0014bf10 *p;   /* +0x0 */
} Obj_FUN_0014bf10;

s32 AnimResGetFrameKeyList_14bf10(Obj_FUN_0014bf10 *o)
{
    Sub_FUN_0014bf10 *p;
    u8 live;

    p = o->p;
    live = p != 0;
    if (live != 0) {
        return p->val;
    }
    return 0;
}
