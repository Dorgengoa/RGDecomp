#include "types.h"

/* Null-checked pointer chase; the likely branch carries -1 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0033b160 {
    s16 val;         /* +0x0 */
} Sub_FUN_0033b160;

typedef struct Obj_FUN_0033b160 {
    u8 pad000[0x68];
    Sub_FUN_0033b160 *p;         /* +0x68 */
} Obj_FUN_0033b160;

s32 TreasureBoxGetRecId_33b160(Obj_FUN_0033b160 *o)
{
    Sub_FUN_0033b160 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
