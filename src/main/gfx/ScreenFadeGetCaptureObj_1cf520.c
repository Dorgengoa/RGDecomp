#include "types.h"

/* Read the s32 at +0x59AC. */

typedef struct Obj_FUN_001cf520 {
    u8 pad000[0x59AC];
    s32 field;         /* +0x59AC */
} Obj_FUN_001cf520;

s32 ScreenFadeGetCaptureObj_1cf520(Obj_FUN_001cf520 *o)
{
    return o->field;
}
