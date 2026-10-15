#include "types.h"

/* Read the s16 at +0x2FC. */

typedef struct Obj_FUN_00366ac0 {
    u8 pad000[0x2FC];
    s16 field;         /* +0x2FC */
} Obj_FUN_00366ac0;

s16 EvMapObjDataGetNodeCount_366ac0(Obj_FUN_00366ac0 *o)
{
    return o->field;
}
