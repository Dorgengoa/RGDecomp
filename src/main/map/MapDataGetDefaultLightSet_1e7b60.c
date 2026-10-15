#include "types.h"

/* Read the s8 at +0x20. */

typedef struct Obj_FUN_001e7b60 {
    u8 pad000[0x20];
    s8 field;         /* +0x20 */
} Obj_FUN_001e7b60;

s8 MapDataGetDefaultLightSet_1e7b60(Obj_FUN_001e7b60 *o)
{
    return o->field;
}
