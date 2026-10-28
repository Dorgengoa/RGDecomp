/* rgp:protos */
#define RGP_SELF_MenuWinSetSubtractBlend_26c2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xDC. */

typedef struct Obj_FUN_0026c2e0 {
    u8 pad000[0xDC];
    s32 field;         /* +0xDC */
} Obj_FUN_0026c2e0;

void MenuWinSetSubtractBlend_26c2e0(Obj_FUN_0026c2e0 *o, s32 value)
{
    o->field = value;
}
