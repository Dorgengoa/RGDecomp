/* rgp:protos */
#define RGP_SELF_MapCaptionGetOffsetY_33f1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x28. */

typedef struct Obj_FUN_0033f1e0 {
    u8 pad000[0x28];
    s32 field;         /* +0x28 */
} Obj_FUN_0033f1e0;

s32 MapCaptionGetOffsetY_33f1e0(Obj_FUN_0033f1e0 *o)
{
    return o->field;
}
