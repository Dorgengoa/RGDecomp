#include "types.h"

/* Read the f32 at +0x4. */

typedef struct Obj_FUN_001e92f0 {
    u8 pad000[0x4];
    f32 field;         /* +0x4 */
} Obj_FUN_001e92f0;

f32 MapLinkGetX_1e92f0(Obj_FUN_001e92f0 *o)
{
    return o->field;
}
