/* rgp:protos */
#define RGP_SELF_MenuWinGetDrawMode_26c290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_0026c290 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0026c290;

s32 MenuWinGetDrawMode_26c290(Obj_FUN_0026c290 *o)
{
    return o->field;
}
