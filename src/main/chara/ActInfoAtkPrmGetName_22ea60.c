#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_0022ea60 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0022ea60;

s32 ActInfoAtkPrmGetName_22ea60(Obj_FUN_0022ea60 *o)
{
    return o->field;
}
