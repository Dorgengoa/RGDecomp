#include "types.h"

/* Write the s32 at +0x8. */

typedef struct Obj_FUN_0033eb60 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_0033eb60;

void UiPanelSetWidgetPoolSize_33eb60(Obj_FUN_0033eb60 *o, s32 value)
{
    o->field = value;
}
