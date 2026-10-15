#include "types.h"

/* Write the s16 at +0xE8. */

typedef struct Obj_FUN_00336090 {
    u8 pad000[0xE8];
    s16 field;         /* +0xE8 */
} Obj_FUN_00336090;

void EvObjLiftSetTargetPairCount_336090(Obj_FUN_00336090 *o, s16 value)
{
    o->field = value;
}
