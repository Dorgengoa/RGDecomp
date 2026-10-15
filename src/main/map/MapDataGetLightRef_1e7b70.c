#include "types.h"

/* Read the s16 at +0x1E. */

typedef struct Obj_FUN_001e7b70 {
    u8 pad000[0x1E];
    s16 field;         /* +0x1E */
} Obj_FUN_001e7b70;

s16 MapDataGetLightRef_1e7b70(Obj_FUN_001e7b70 *o)
{
    return o->field;
}
