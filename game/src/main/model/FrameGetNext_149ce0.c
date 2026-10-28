/* rgp:protos */
#define RGP_SELF_FrameGetNext_149ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_00149ce0 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_00149ce0;

s32 FrameGetNext_149ce0(Obj_FUN_00149ce0 *o)
{
    return o->field;
}
