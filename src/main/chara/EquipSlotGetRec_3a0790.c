#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_003a0790 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_003a0790;

s32 EquipSlotGetRec_3a0790(Obj_FUN_003a0790 *o)
{
    return o->field;
}
