#include "types.h"

/* Is the s32 at +0x0 non-zero? */

typedef struct Obj_FUN_0042d010 {
    s32 field;         /* +0x0 */
} Obj_FUN_0042d010;

u8 UskMemoryRefIsSet_42d010(Obj_FUN_0042d010 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
