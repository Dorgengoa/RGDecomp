/* rgp:protos */
#define RGP_SELF_UiPanelGetWidgetDefs_33e960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_0033e960 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_0033e960;

s32 UiPanelGetWidgetDefs_33e960(Obj_FUN_0033e960 *o)
{
    return o->field;
}
