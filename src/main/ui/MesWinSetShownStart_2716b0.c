#include "types.h"

/* Write the s32 at +0xC0. */

typedef struct Obj_FUN_002716b0 {
    u8 pad000[0xC0];
    s32 field;         /* +0xC0 */
} Obj_FUN_002716b0;

void MesWinSetShownStart_2716b0(Obj_FUN_002716b0 *o, s32 value)
{
    o->field = value;
}
