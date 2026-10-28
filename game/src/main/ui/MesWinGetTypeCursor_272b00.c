/* rgp:protos */
#define RGP_SELF_MesWinGetTypeCursor_272b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xB8. */

typedef struct Obj_FUN_00272b00 {
    u8 pad000[0xB8];
    f32 field;         /* +0xB8 */
} Obj_FUN_00272b00;

f32 MesWinGetTypeCursor_272b00(Obj_FUN_00272b00 *o)
{
    return o->field;
}
