#include "types.h"

/* Read the s16 at +0x148. */

typedef struct Obj_FUN_003532f0 {
    u8 pad000[0x148];
    s16 field;         /* +0x148 */
} Obj_FUN_003532f0;

s16 EvNodeAttachObjGetPlayState_3532f0(Obj_FUN_003532f0 *o)
{
    return o->field;
}
