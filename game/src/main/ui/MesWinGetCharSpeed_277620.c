/* rgp:protos */
#define RGP_SELF_MesWinGetCharSpeed_277620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xB0. */

typedef struct Obj_FUN_00277620 {
    u8 pad000[0xB0];
    f32 field;         /* +0xB0 */
} Obj_FUN_00277620;

f32 MesWinGetCharSpeed_277620(Obj_FUN_00277620 *o)
{
    return o->field;
}
