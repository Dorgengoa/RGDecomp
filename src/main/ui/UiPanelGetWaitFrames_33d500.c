#include "types.h"

/* Read the s32 at +0x60. */

typedef struct Obj_FUN_0033d500 {
    u8 pad000[0x60];
    s32 field;         /* +0x60 */
} Obj_FUN_0033d500;

s32 UiPanelGetWaitFrames_33d500(Obj_FUN_0033d500 *o)
{
    return o->field;
}
