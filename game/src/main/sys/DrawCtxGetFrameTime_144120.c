/* rgp:protos */
#define RGP_SELF_DrawCtxGetFrameTime_144120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xF10. */

typedef struct Obj_FUN_00144120 {
    u8 pad000[0xF10];
    f32 field;         /* +0xF10 */
} Obj_FUN_00144120;

f32 DrawCtxGetFrameTime_144120(Obj_FUN_00144120 *o)
{
    return o->field;
}
