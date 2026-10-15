#include "types.h"

/* Null-checked pointer chase; the likely branch carries -1 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0033b140 {
    u8 pad000[0x4];
    s16 val;         /* +0x4 */
} Sub_FUN_0033b140;

typedef struct Obj_FUN_0033b140 {
    u8 pad000[0x68];
    Sub_FUN_0033b140 *p;         /* +0x68 */
} Obj_FUN_0033b140;

s32 TreasureBoxGetSortKey_33b140(Obj_FUN_0033b140 *o)
{
    Sub_FUN_0033b140 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
