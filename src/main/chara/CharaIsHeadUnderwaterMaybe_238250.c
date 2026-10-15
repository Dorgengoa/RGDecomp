#include "types.h"

/* Is the s16 at +0x412 non-zero? */

typedef struct Obj_FUN_00238250 {
    u8 pad000[0x412];
    s16 field;         /* +0x412 */
} Obj_FUN_00238250;

u8 CharaIsHeadUnderwaterMaybe_238250(Obj_FUN_00238250 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
