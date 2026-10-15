#include "types.h"

/* Read the s32 at +0x50. */

typedef struct Obj_FUN_00340000 {
    u8 pad000[0x50];
    s32 field;         /* +0x50 */
} Obj_FUN_00340000;

s32 CaptionCfgGetGlyphList_340000(Obj_FUN_00340000 *o)
{
    return o->field;
}
