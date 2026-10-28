/* rgp:protos */
#define RGP_SELF_MinimapSlotIsActive_322510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1A0. */

typedef struct Obj_FUN_00322510 {
    u8 pad000[0x1A0];
    s32 field;         /* +0x1A0 */
} Obj_FUN_00322510;

s32 MinimapSlotIsActive_322510(Obj_FUN_00322510 *o)
{
    return o->field;
}
