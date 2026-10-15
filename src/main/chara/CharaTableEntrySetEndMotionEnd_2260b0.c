#include "types.h"

/* Zero the s16 at +0x3A. */

typedef struct Obj_FUN_002260b0 {
    u8 pad000[0x3A];
    s16 field;         /* +0x3A */
} Obj_FUN_002260b0;

void CharaTableEntrySetEndMotionEnd_2260b0(Obj_FUN_002260b0 *o)
{
    o->field = 0;
}
