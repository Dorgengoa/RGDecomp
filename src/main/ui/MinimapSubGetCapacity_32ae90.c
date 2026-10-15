#include "types.h"

/* Read the s16 at +0xA. */

typedef struct Obj_FUN_0032ae90 {
    u8 pad000[0xA];
    s16 field;         /* +0xA */
} Obj_FUN_0032ae90;

s16 MinimapSubGetCapacity_32ae90(Obj_FUN_0032ae90 *o)
{
    return o->field;
}
