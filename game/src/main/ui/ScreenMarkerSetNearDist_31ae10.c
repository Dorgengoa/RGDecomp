/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetNearDist_31ae10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x148. */

typedef struct Obj_FUN_0031ae10 {
    u8 pad000[0x148];
    f32 field;         /* +0x148 */
} Obj_FUN_0031ae10;

void ScreenMarkerSetNearDist_31ae10(Obj_FUN_0031ae10 *o, f32 value)
{
    o->field = value;
}
