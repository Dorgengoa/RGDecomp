/* rgp:protos */
#define RGP_SELF_MesWinGetCharCount_274c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1928. */

typedef struct Obj_FUN_00274c70 {
    u8 pad000[0x1928];
    s32 field;         /* +0x1928 */
} Obj_FUN_00274c70;

s32 MesWinGetCharCount_274c70(Obj_FUN_00274c70 *o)
{
    return o->field;
}
