/* rgp:protos */
#define RGP_SELF_UiPanelGetGlyphSpacing_33dfc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x50. */

typedef struct Obj_FUN_0033dfc0 {
    u8 pad000[0x50];
    s32 field;         /* +0x50 */
} Obj_FUN_0033dfc0;

s32 UiPanelGetGlyphSpacing_33dfc0(Obj_FUN_0033dfc0 *o)
{
    return o->field;
}
