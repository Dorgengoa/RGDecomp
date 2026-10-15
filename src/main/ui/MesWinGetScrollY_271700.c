#include "types.h"

/* Read the s32 at +0x192C. */

typedef struct Obj_FUN_00271700 {
    u8 pad000[0x192C];
    s32 field;         /* +0x192C */
} Obj_FUN_00271700;

s32 MesWinGetScrollY_271700(Obj_FUN_00271700 *o)
{
    return o->field;
}
