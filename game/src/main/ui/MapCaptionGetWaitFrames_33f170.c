/* rgp:protos */
#define RGP_SELF_MapCaptionGetWaitFrames_33f170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x34. */

typedef struct Obj_FUN_0033f170 {
    u8 pad000[0x34];
    s32 field;         /* +0x34 */
} Obj_FUN_0033f170;

s32 MapCaptionGetWaitFrames_33f170(Obj_FUN_0033f170 *o)
{
    return o->field;
}
