/* rgp:protos */
#define RGP_SELF_MenuWinSetAlphaTest_26c250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xD0. */

typedef struct Obj_FUN_0026c250 {
    u8 pad000[0xD0];
    s32 field;         /* +0xD0 */
} Obj_FUN_0026c250;

void MenuWinSetAlphaTest_26c250(Obj_FUN_0026c250 *o, s32 value)
{
    o->field = value;
}
