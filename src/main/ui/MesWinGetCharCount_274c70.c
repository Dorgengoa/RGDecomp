#include "types.h"

/* Read the s32 at +0x1928. */

typedef struct Obj_FUN_00274c70 {
    u8 pad000[0x1928];
    s32 field;         /* +0x1928 */
} Obj_FUN_00274c70;

s32 MesWinGetCharCount_274c70(Obj_FUN_00274c70 *o)
{
    return o->field;
}
