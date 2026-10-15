#include "types.h"

/* Read the f32 at +0x48. */

typedef struct Obj_FUN_001e9890 {
    u8 pad000[0x48];
    f32 field;         /* +0x48 */
} Obj_FUN_001e9890;

f32 AreaBoxGetBottomY_1e9890(Obj_FUN_001e9890 *o)
{
    return o->field;
}
