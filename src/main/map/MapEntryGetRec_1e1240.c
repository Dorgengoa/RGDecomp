#include "types.h"

/* Read the s32 at +0x790. */

typedef struct Obj_FUN_001e1240 {
    u8 pad000[0x790];
    s32 field;         /* +0x790 */
} Obj_FUN_001e1240;

s32 MapEntryGetRec_1e1240(Obj_FUN_001e1240 *o)
{
    return o->field;
}
