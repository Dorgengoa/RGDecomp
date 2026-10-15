#include "types.h"

/* Read the f32 at +0x144. */

typedef struct Obj_FUN_0031ae40 {
    u8 pad000[0x144];
    f32 field;         /* +0x144 */
} Obj_FUN_0031ae40;

f32 ScreenMarkerGetFarDist_31ae40(Obj_FUN_0031ae40 *o)
{
    return o->field;
}
