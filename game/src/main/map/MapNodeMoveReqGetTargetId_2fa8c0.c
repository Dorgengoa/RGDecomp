/* rgp:protos */
#define RGP_SELF_MapNodeMoveReqGetTargetId_2fa8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x20. */

typedef struct Obj_FUN_002fa8c0 {
    u8 pad000[0x20];
    s32 field;         /* +0x20 */
} Obj_FUN_002fa8c0;

s32 MapNodeMoveReqGetTargetId_2fa8c0(Obj_FUN_002fa8c0 *o)
{
    return o->field;
}
