/* rgp:protos */
#define RGP_SELF_MenuWinSetActive_26c3f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_0026c3f0 {
    s32 field;         /* +0x00 */
} Obj_FUN_0026c3f0;

void MenuWinSetActive_26c3f0(Obj_FUN_0026c3f0 *o, s32 value)
{
    o->field = value;
}
