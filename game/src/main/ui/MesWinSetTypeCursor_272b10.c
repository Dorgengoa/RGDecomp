/* rgp:protos */
#define RGP_SELF_MesWinSetTypeCursor_272b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0xB8. */

typedef struct Obj_FUN_00272b10 {
    u8 pad000[0xB8];
    f32 field;         /* +0xB8 */
} Obj_FUN_00272b10;

void MesWinSetTypeCursor_272b10(Obj_FUN_00272b10 *o, f32 value)
{
    o->field = value;
}
