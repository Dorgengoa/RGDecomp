#include "types.h"

/* Null-checked chase with the condition MATERIALISED: retail's sltu before
   the beql is a u8 bool built from the comparison, not a bare test. */

typedef struct Sub_FUN_0014bef0 {
    u8 pad000[0x28];
    s32 m28;           /* +0x28 */
} Sub_FUN_0014bef0;

typedef struct Obj_FUN_0014bef0 {
    Sub_FUN_0014bef0 *p;
} Obj_FUN_0014bef0;

s32 AnimResGetMaterialKeyList_14bef0(Obj_FUN_0014bef0 *o)
{
    Sub_FUN_0014bef0 *p;
    u8 live;

    p = o->p;
    live = p != 0;
    if (live != 0) {
        return p->m28;
    }
    return 0;
}
