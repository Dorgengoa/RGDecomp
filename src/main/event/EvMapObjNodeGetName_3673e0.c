#include "types.h"

/* Read the s32 at +0x140. */

typedef struct Obj_FUN_003673e0 {
    u8 pad000[0x140];
    s32 field;         /* +0x140 */
} Obj_FUN_003673e0;

s32 EvMapObjNodeGetName_3673e0(Obj_FUN_003673e0 *o)
{
    return o->field;
}
