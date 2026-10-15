#include "types.h"

/* Is the s32 at +0x28 non-zero? */

typedef struct Obj_FUN_0014d380 {
    u8 pad000[0x28];
    s32 field;         /* +0x28 */
} Obj_FUN_0014d380;

u8 MemStackHasBase_14d380(Obj_FUN_0014d380 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
