#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_001ce1c0 {
    s32 field;         /* +0x00 */
} Obj_FUN_001ce1c0;

s32 S16ArrayGetData_1ce1c0(Obj_FUN_001ce1c0 *o)
{
    return o->field;
}
