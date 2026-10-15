#include "types.h"

/* Read the s32 at +0x1948. */

typedef struct Obj_FUN_00271ec0 {
    u8 pad000[0x1948];
    s32 field;         /* +0x1948 */
} Obj_FUN_00271ec0;

s32 MesWinGetPageFrames_271ec0(Obj_FUN_00271ec0 *o)
{
    return o->field;
}
