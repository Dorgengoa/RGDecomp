/* rgp:protos */
#define RGP_SELF_MesWinGetScrollTarget_2716d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1930. */

typedef struct Obj_FUN_002716d0 {
    u8 pad000[0x1930];
    s32 field;         /* +0x1930 */
} Obj_FUN_002716d0;

s32 MesWinGetScrollTarget_2716d0(Obj_FUN_002716d0 *o)
{
    return o->field;
}
