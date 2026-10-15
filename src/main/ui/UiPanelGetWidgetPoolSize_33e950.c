#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_0033e950 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_0033e950;

s32 UiPanelGetWidgetPoolSize_33e950(Obj_FUN_0033e950 *o)
{
    return o->field;
}
