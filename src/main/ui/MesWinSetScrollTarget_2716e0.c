#include "types.h"

/* Write the s32 at +0x1930. */

typedef struct Obj_FUN_002716e0 {
    u8 pad000[0x1930];
    s32 field;         /* +0x1930 */
} Obj_FUN_002716e0;

void MesWinSetScrollTarget_2716e0(Obj_FUN_002716e0 *o, s32 value)
{
    o->field = value;
}
