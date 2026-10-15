#include "types.h"

/* Write the u8 at +0x4C. */

typedef struct Obj_FUN_0033fe70 {
    u8 pad000[0x4C];
    u8 field;         /* +0x4C */
} Obj_FUN_0033fe70;

void CaptionCfgSetGlyphBase_33fe70(Obj_FUN_0033fe70 *o, u8 value)
{
    o->field = value;
}
