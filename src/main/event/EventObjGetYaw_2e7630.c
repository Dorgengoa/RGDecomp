#include "types.h"

/* Read the f32 at +0x10. */

typedef struct Obj_FUN_002e7630 {
    u8 pad000[0x10];
    f32 field;         /* +0x10 */
} Obj_FUN_002e7630;

f32 EventObjGetYaw_2e7630(Obj_FUN_002e7630 *o)
{
    return o->field;
}
