/* rgp:protos */
#define RGP_SELF_FuncDataTableIterEnd_1908a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x8. */

typedef struct Obj_FUN_001908a0 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_001908a0;

void FuncDataTableIterEnd_1908a0(Obj_FUN_001908a0 *o)
{
    o->field = 0;
}
