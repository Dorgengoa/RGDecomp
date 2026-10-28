/* rgp:protos */
#define RGP_SELF_EvFollowObjGetVolumeRec_2f80b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x114. */

typedef struct Obj_FUN_002f80b0 {
    u8 pad000[0x114];
    s32 field;         /* +0x114 */
} Obj_FUN_002f80b0;

s32 EvFollowObjGetVolumeRec_2f80b0(Obj_FUN_002f80b0 *o)
{
    return o->field;
}
