#include "types.h"

/* Null-checked pointer chase; the likely branch carries -1 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0033ad90 {
    u8 pad000[0xE];
    s16 val;         /* +0xE */
} Sub_FUN_0033ad90;

typedef struct Obj_FUN_0033ad90 {
    u8 pad000[0x68];
    Sub_FUN_0033ad90 *p;         /* +0x68 */
} Obj_FUN_0033ad90;

s32 TreasureBoxGetItemId_33ad90(Obj_FUN_0033ad90 *o)
{
    Sub_FUN_0033ad90 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
