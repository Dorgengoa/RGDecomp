#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_003403a0 {
    s32 field;         /* +0x00 */
} Obj_FUN_003403a0;

void CaptionGlyphNodeSetKey_3403a0(Obj_FUN_003403a0 *o, s32 value)
{
    o->field = value;
}
