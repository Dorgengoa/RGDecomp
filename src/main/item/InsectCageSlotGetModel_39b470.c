#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_0039b470 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_0039b470;

s32 InsectCageSlotGetModel_39b470(Obj_FUN_0039b470 *o)
{
    return o->field;
}
