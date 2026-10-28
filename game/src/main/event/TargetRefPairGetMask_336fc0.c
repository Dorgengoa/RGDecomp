/* rgp:protos */
#define RGP_SELF_TargetRefPairGetMask_336fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x64. */

typedef struct Obj_FUN_00336fc0 {
    u8 pad000[0x64];
    s32 field;         /* +0x64 */
} Obj_FUN_00336fc0;

s32 TargetRefPairGetMask_336fc0(Obj_FUN_00336fc0 *o)
{
    return o->field;
}
