#include "types.h"

/* Read the f32 at +0x8. */

typedef struct Obj_FUN_001e92d0 {
    u8 pad000[0x8];
    f32 field;         /* +0x8 */
} Obj_FUN_001e92d0;

f32 MapLinkGetY_1e92d0(Obj_FUN_001e92d0 *o)
{
    return o->field;
}
