/* rgp:protos */
#define RGP_SELF_ScreenMarkerGetNearDist_31ae20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x148. */

typedef struct Obj_FUN_0031ae20 {
    u8 pad000[0x148];
    f32 field;         /* +0x148 */
} Obj_FUN_0031ae20;

f32 ScreenMarkerGetNearDist_31ae20(Obj_FUN_0031ae20 *o)
{
    return o->field;
}
