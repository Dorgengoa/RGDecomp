#include "types.h"

/* Read the s16 at +0x158. */

typedef struct Obj_FUN_00352020 {
    u8 pad000[0x158];
    s16 field;         /* +0x158 */
} Obj_FUN_00352020;

s16 EvM05ChangeGetPlayState_352020(Obj_FUN_00352020 *o)
{
    return o->field;
}
