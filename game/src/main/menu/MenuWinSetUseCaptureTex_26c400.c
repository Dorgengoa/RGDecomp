/* rgp:protos */
#define RGP_SELF_MenuWinSetUseCaptureTex_26c400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xB8. */

typedef struct Obj_FUN_0026c400 {
    u8 pad000[0xB8];
    s32 field;         /* +0xB8 */
} Obj_FUN_0026c400;

void MenuWinSetUseCaptureTex_26c400(Obj_FUN_0026c400 *o, s32 value)
{
    o->field = value;
}
