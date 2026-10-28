/* rgp:protos */
#define RGP_SELF_DebugMenuWidgetGetChildCount_209d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x1C. */

typedef struct Obj_FUN_00209d70 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_00209d70;

s16 DebugMenuWidgetGetChildCount_209d70(Obj_FUN_00209d70 *o)
{
    return o->field;
}
