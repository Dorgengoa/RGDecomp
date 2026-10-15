#include "types.h"

/* Read the s16 at +0xC8. */

typedef struct Obj_FUN_001dfd20 {
    u8 pad000[0xC8];
    s16 field;         /* +0xC8 */
} Obj_FUN_001dfd20;

s16 MapBlockGetEntryCount_1dfd20(Obj_FUN_001dfd20 *o)
{
    return o->field;
}
