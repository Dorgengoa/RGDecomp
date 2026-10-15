#include "types.h"

/* Write the s16 at +0x2FC. */

typedef struct Obj_FUN_00366ab0 {
    u8 pad000[0x2FC];
    s16 field;         /* +0x2FC */
} Obj_FUN_00366ab0;

void EvMapObjDataSetNodeCount_366ab0(Obj_FUN_00366ab0 *o, s16 value)
{
    o->field = value;
}
