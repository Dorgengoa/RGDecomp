#include "types.h"

/* Write the s32 at +0x14. */

typedef struct Obj_FUN_0033eab0 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_0033eab0;

void CaptionPanelSetGlyphList_33eab0(Obj_FUN_0033eab0 *o, s32 value)
{
    o->field = value;
}
