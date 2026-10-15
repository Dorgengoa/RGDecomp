#include "types.h"

/* Is the s32 at +0x0 non-zero? */

typedef struct Obj_FUN_003849d0 {
    s32 field;         /* +0x0 */
} Obj_FUN_003849d0;

u8 MenuObjSlotIsActive_3849d0(Obj_FUN_003849d0 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
