#include "types.h"

/* Read the s32 at +0x3C. */

typedef struct Obj_FUN_0033e8b0 {
    u8 pad000[0x3C];
    s32 field;         /* +0x3C */
} Obj_FUN_0033e8b0;

s32 UiPanelGetTimer1_33e8b0(Obj_FUN_0033e8b0 *o)
{
    return o->field;
}
