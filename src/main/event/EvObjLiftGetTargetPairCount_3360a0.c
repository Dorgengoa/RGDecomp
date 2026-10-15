#include "types.h"

/* Read the s16 at +0xE8. */

typedef struct Obj_FUN_003360a0 {
    u8 pad000[0xE8];
    s16 field;         /* +0xE8 */
} Obj_FUN_003360a0;

s16 EvObjLiftGetTargetPairCount_3360a0(Obj_FUN_003360a0 *o)
{
    return o->field;
}
