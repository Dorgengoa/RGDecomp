#include "types.h"

/* Read the f32 at +0x150. */

typedef struct Obj_FUN_0031aeb0 {
    u8 pad000[0x150];
    f32 field;         /* +0x150 */
} Obj_FUN_0031aeb0;

f32 ScreenMarkerGetMasterAlpha_31aeb0(Obj_FUN_0031aeb0 *o)
{
    return o->field;
}
