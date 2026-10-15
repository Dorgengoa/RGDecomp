#include "types.h"

/* Null-checked pointer chase; the likely branch carries -1 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003a0760 {
    s16 val;         /* +0x0 */
} Sub_FUN_003a0760;

typedef struct Obj_FUN_003a0760 {
    u8 pad000[0x4];
    Sub_FUN_003a0760 *p;         /* +0x4 */
} Obj_FUN_003a0760;

s32 EquipSlotGetRecId_3a0760(Obj_FUN_003a0760 *o)
{
    Sub_FUN_003a0760 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
