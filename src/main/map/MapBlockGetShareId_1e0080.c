#include "types.h"

/* Read the s16 at +0x6A. */

typedef struct Obj_FUN_001e0080 {
    u8 pad000[0x6A];
    s16 field;         /* +0x6A */
} Obj_FUN_001e0080;

s16 MapBlockGetShareId_1e0080(Obj_FUN_001e0080 *o)
{
    return o->field;
}
