#include "types.h"

/* Read the s16 at +0x2FE. */

typedef struct Obj_FUN_00366b70 {
    u8 pad000[0x2FE];
    s16 field;         /* +0x2FE */
} Obj_FUN_00366b70;

s16 EvMapObjGetId_366b70(Obj_FUN_00366b70 *o)
{
    return o->field;
}
