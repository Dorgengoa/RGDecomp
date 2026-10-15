#include "types.h"

/* Write the s32 at +0x1928. */

typedef struct Obj_FUN_00274c80 {
    u8 pad000[0x1928];
    s32 field;         /* +0x1928 */
} Obj_FUN_00274c80;

void MesWinSetCharCount_274c80(Obj_FUN_00274c80 *o, s32 value)
{
    o->field = value;
}
