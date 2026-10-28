/* rgp:protos */
#define RGP_SELF_EvFollowObjGetPathRec_2f80c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x110. */

typedef struct Obj_FUN_002f80c0 {
    u8 pad000[0x110];
    s32 field;         /* +0x110 */
} Obj_FUN_002f80c0;

s32 EvFollowObjGetPathRec_2f80c0(Obj_FUN_002f80c0 *o)
{
    return o->field;
}
