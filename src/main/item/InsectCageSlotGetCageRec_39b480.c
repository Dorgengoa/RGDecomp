#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_0039b480 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_0039b480;

s32 InsectCageSlotGetCageRec_39b480(Obj_FUN_0039b480 *o)
{
    return o->field;
}
