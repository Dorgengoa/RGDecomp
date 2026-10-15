#include "types.h"

/* Null-checked pointer chase; the likely branch carries -1 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0033adb0 {
    u8 pad000[0xC];
    s16 val;         /* +0xC */
} Sub_FUN_0033adb0;

typedef struct Obj_FUN_0033adb0 {
    u8 pad000[0x68];
    Sub_FUN_0033adb0 *p;         /* +0x68 */
} Obj_FUN_0033adb0;

s32 TreasureBoxGetKind_33adb0(Obj_FUN_0033adb0 *o)
{
    Sub_FUN_0033adb0 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
