/* rgp:protos */
#define RGP_SELF_CaptionPanelGetOffsetX_33df30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x54. */

typedef struct Obj_FUN_0033df30 {
    u8 pad000[0x54];
    s32 field;         /* +0x54 */
} Obj_FUN_0033df30;

s32 CaptionPanelGetOffsetX_33df30(Obj_FUN_0033df30 *o)
{
    return o->field;
}
