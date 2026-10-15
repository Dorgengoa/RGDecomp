#include "types.h"

/* Read the s8 at +0x22. */

typedef struct Obj_FUN_001e7a00 {
    u8 pad000[0x22];
    s8 field;         /* +0x22 */
} Obj_FUN_001e7a00;

s8 MapDataGetState_1e7a00(Obj_FUN_001e7a00 *o)
{
    return o->field;
}
