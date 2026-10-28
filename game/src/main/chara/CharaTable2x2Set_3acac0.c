/* rgp:protos */
#define RGP_SELF_CharaTable2x2Set_3acac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct ObjACAC0 {
    u8 pad0[0x248];
    s16 arr248[2][2];
} ObjACAC0;

void CharaTable2x2Set_3acac0(ObjACAC0 *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    if (arg1 < 0 || arg1 >= 2 || arg3 < 0 || arg3 >= 2) {
        return;
    }
    arg0->arr248[arg1][arg3] = arg2;
}
