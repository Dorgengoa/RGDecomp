/* rgp:protos */
#define RGP_SELF_DynClothClearWind_169400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x120. */

typedef struct Obj_FUN_00169400 {
    u8 pad000[0x120];
    s32 field;         /* +0x120 */
} Obj_FUN_00169400;

void DynClothClearWind_169400(Obj_FUN_00169400 *o)
{
    o->field = 0;
}
