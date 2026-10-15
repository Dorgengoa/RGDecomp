#include "types.h"

/* Read the s16 at +0x1E. */

typedef struct Obj_FUN_0039bb00 {
    u8 pad000[0x1E];
    s16 field;         /* +0x1E */
} Obj_FUN_0039bb00;

s16 InsectCageSlotGetState_39bb00(Obj_FUN_0039bb00 *o)
{
    return o->field;
}
