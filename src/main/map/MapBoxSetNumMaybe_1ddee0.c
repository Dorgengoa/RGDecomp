#include "types.h"

/* Write the s16 at +0x4C. */

typedef struct Obj_FUN_001ddee0 {
    u8 pad000[0x4C];
    s16 field;         /* +0x4C */
} Obj_FUN_001ddee0;

void MapBoxSetNumMaybe_1ddee0(Obj_FUN_001ddee0 *o, s16 value)
{
    o->field = value;
}
