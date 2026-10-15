#include "types.h"

/* Read the s32 at +0x140. */

typedef struct Obj_FUN_00352040 {
    u8 pad000[0x140];
    s32 field;         /* +0x140 */
} Obj_FUN_00352040;

s32 EvM05ChangeGetModelName_352040(Obj_FUN_00352040 *o)
{
    return o->field;
}
