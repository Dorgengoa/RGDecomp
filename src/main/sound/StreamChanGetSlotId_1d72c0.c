#include "types.h"

/* Read the s16 at +0x80. */

typedef struct Obj_FUN_001d72c0 {
    u8 pad000[0x80];
    s16 field;         /* +0x80 */
} Obj_FUN_001d72c0;

s16 StreamChanGetSlotId_1d72c0(Obj_FUN_001d72c0 *o)
{
    return o->field;
}
