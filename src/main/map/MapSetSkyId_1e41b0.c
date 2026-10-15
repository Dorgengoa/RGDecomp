#include "types.h"

/* Write the s16 at +0x0. */

typedef struct Obj_FUN_001e41b0 {
    s16 field;         /* +0x00 */
} Obj_FUN_001e41b0;

void MapSetSkyId_1e41b0(Obj_FUN_001e41b0 *o, s16 value)
{
    o->field = value;
}
