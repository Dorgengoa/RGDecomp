#include "types.h"

/* Write the s32 at +0x50. */

typedef struct Obj_FUN_0033dfb0 {
    u8 pad000[0x50];
    s32 field;         /* +0x50 */
} Obj_FUN_0033dfb0;

void UiPanelSetGlyphSpacing_33dfb0(Obj_FUN_0033dfb0 *o, s32 value)
{
    o->field = value;
}
