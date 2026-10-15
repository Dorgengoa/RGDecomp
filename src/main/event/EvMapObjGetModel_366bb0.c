#include "types.h"

/* Read the s32 at +0x220. */

typedef struct Obj_FUN_00366bb0 {
    u8 pad000[0x220];
    s32 field;         /* +0x220 */
} Obj_FUN_00366bb0;

s32 EvMapObjGetModel_366bb0(Obj_FUN_00366bb0 *o)
{
    return o->field;
}
