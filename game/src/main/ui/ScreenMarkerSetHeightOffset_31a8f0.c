/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetHeightOffset_31a8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x14C. */

typedef struct Obj_FUN_0031a8f0 {
    u8 pad000[0x14C];
    f32 field;         /* +0x14C */
} Obj_FUN_0031a8f0;

void ScreenMarkerSetHeightOffset_31a8f0(Obj_FUN_0031a8f0 *o, f32 value)
{
    o->field = value;
}
