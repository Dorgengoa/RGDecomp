#include "types.h"

/* Write the f32 at +0x88. */

typedef struct Obj_FUN_001d7000 {
    u8 pad000[0x88];
    f32 field;         /* +0x88 */
} Obj_FUN_001d7000;

void StreamChanSetGain_1d7000(Obj_FUN_001d7000 *o, f32 value)
{
    o->field = value;
}
