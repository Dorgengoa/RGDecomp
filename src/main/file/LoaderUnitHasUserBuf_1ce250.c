#include "types.h"

/* Is the s16 at +0x86 non-zero? */

typedef struct Obj_FUN_001ce250 {
    u8 pad000[0x86];
    s16 field;         /* +0x86 */
} Obj_FUN_001ce250;

u8 LoaderUnitHasUserBuf_1ce250(Obj_FUN_001ce250 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
