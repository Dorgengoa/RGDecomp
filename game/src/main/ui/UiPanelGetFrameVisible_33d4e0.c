/* rgp:protos */
#define RGP_SELF_UiPanelGetFrameVisible_33d4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x64. */

typedef struct Obj_FUN_0033d4e0 {
    u8 pad000[0x64];
    s32 field;         /* +0x64 */
} Obj_FUN_0033d4e0;

s32 UiPanelGetFrameVisible_33d4e0(Obj_FUN_0033d4e0 *o)
{
    return o->field;
}
