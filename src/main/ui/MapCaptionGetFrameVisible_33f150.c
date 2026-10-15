#include "types.h"

/* Read the s32 at +0x38. */

typedef struct Obj_FUN_0033f150 {
    u8 pad000[0x38];
    s32 field;         /* +0x38 */
} Obj_FUN_0033f150;

s32 MapCaptionGetFrameVisible_33f150(Obj_FUN_0033f150 *o)
{
    return o->field;
}
