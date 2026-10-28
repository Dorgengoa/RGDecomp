/* rgp:protos */
#define RGP_SELF_EvM05ChangeGetMotionName_352030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x144. */

typedef struct Obj_FUN_00352030 {
    u8 pad000[0x144];
    s32 field;         /* +0x144 */
} Obj_FUN_00352030;

s32 EvM05ChangeGetMotionName_352030(Obj_FUN_00352030 *o)
{
    return o->field;
}
