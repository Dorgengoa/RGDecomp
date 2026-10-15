#include "types.h"

/* Read the s32 at +0xF0. */

typedef struct Obj_FUN_00336130 {
    u8 pad000[0xF0];
    s32 field;         /* +0xF0 */
} Obj_FUN_00336130;

s32 EvObjLiftGetPathRec_336130(Obj_FUN_00336130 *o)
{
    return o->field;
}
