/* rgp:protos */
#define RGP_SELF_ScreenMarkerGetHeightOffset_31a8e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x14C. */

typedef struct Obj_FUN_0031a8e0 {
    u8 pad000[0x14C];
    f32 field;         /* +0x14C */
} Obj_FUN_0031a8e0;

f32 ScreenMarkerGetHeightOffset_31a8e0(Obj_FUN_0031a8e0 *o)
{
    return o->field;
}
