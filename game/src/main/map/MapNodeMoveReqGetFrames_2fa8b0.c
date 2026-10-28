/* rgp:protos */
#define RGP_SELF_MapNodeMoveReqGetFrames_2fa8b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x24. */

typedef struct Obj_FUN_002fa8b0 {
    u8 pad000[0x24];
    s32 field;         /* +0x24 */
} Obj_FUN_002fa8b0;

s32 MapNodeMoveReqGetFrames_2fa8b0(Obj_FUN_002fa8b0 *o)
{
    return o->field;
}
