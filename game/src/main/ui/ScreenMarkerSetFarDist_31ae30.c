/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetFarDist_31ae30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x144. */

typedef struct Obj_FUN_0031ae30 {
    u8 pad000[0x144];
    f32 field;         /* +0x144 */
} Obj_FUN_0031ae30;

void ScreenMarkerSetFarDist_31ae30(Obj_FUN_0031ae30 *o, f32 value)
{
    o->field = value;
}
