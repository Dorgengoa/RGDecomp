#include "types.h"

/* Read the s16 at +0xF8. */

typedef struct Obj_FUN_0029b580 {
    u8 pad000[0xF8];
    s16 field;         /* +0xF8 */
} Obj_FUN_0029b580;

s16 MenuGetListCount_29b580(Obj_FUN_0029b580 *o)
{
    return o->field;
}
