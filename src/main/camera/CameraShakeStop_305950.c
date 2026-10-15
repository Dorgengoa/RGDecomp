#include "types.h"

/* Zero the s32 at +0x2D0. */

typedef struct Obj_FUN_00305950 {
    u8 pad000[0x2D0];
    s32 field;         /* +0x2D0 */
} Obj_FUN_00305950;

void CameraShakeStop_305950(Obj_FUN_00305950 *o)
{
    o->field = 0;
}
