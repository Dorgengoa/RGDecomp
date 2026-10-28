/* rgp:protos */
#define RGP_SELF_CaptionCfgGetTexName_340220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_00340220 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_00340220;

s32 CaptionCfgGetTexName_340220(Obj_FUN_00340220 *o)
{
    return o->field;
}
