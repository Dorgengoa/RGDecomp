/* rgp:protos */
#define RGP_SELF_MesWinSetSeEnabled_272b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x85. */

typedef struct Obj_FUN_00272b50 {
    u8 pad000[0x85];
    u8 field;         /* +0x85 */
} Obj_FUN_00272b50;

void MesWinSetSeEnabled_272b50(Obj_FUN_00272b50 *o, u8 value)
{
    o->field = value;
}
