#include "types.h"

/* Read the s32 at +0xC0. */

typedef struct Obj_FUN_002716a0 {
    u8 pad000[0xC0];
    s32 field;         /* +0xC0 */
} Obj_FUN_002716a0;

s32 MesWinGetShownStart_2716a0(Obj_FUN_002716a0 *o)
{
    return o->field;
}
