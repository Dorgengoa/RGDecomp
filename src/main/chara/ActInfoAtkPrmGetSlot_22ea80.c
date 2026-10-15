#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_0022ea80 {
    s16 field;         /* +0x00 */
} Obj_FUN_0022ea80;

s16 ActInfoAtkPrmGetSlot_22ea80(Obj_FUN_0022ea80 *o)
{
    return o->field;
}
