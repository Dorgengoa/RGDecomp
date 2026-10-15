#include "types.h"

/* Read the f32 at +0xC. */

typedef struct Obj_FUN_00223cb0 {
    u8 pad000[0xC];
    f32 field;         /* +0xC */
} Obj_FUN_00223cb0;

f32 ActCfgTableGetAccelScale_223cb0(Obj_FUN_00223cb0 *o)
{
    return o->field;
}
