#include "types.h"

/* Write the s16 at +0xB4. */

typedef struct Obj_FUN_00277610 {
    u8 pad000[0xB4];
    s16 field;         /* +0xB4 */
} Obj_FUN_00277610;

void MesWinSetInstant_277610(Obj_FUN_00277610 *o, s16 value)
{
    o->field = value;
}
