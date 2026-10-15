#include "types.h"

/* Read the s16 at +0xB4. */

typedef struct Obj_FUN_00277600 {
    u8 pad000[0xB4];
    s16 field;         /* +0xB4 */
} Obj_FUN_00277600;

s16 MesWinGetInstant_277600(Obj_FUN_00277600 *o)
{
    return o->field;
}
