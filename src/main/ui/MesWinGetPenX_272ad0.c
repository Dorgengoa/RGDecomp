#include "types.h"

/* Read the s32 at +0x1934. */

typedef struct Obj_FUN_00272ad0 {
    u8 pad000[0x1934];
    s32 field;         /* +0x1934 */
} Obj_FUN_00272ad0;

s32 MesWinGetPenX_272ad0(Obj_FUN_00272ad0 *o)
{
    return o->field;
}
