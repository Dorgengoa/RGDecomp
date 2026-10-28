/* rgp:protos */
#define RGP_SELF_CharaFindNextLevelRow_3ac830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T_FUN_003ac830 {
    u8 pad000[0x2E];
    s16 f2E;
} T_FUN_003ac830;

typedef struct Obj_FUN_003ac830 {
    u8 pad000[0x230];
    T_FUN_003ac830 *f230;
} Obj_FUN_003ac830;

/*rgp*/

s32 CharaFindNextLevelRow_3ac830(Obj_FUN_003ac830 *o, s32 start)
{
    s32 i;
    s32 r;

    if (o->f230 == 0) {
        return 0;
    }
    for (i = start + 1; i <= o->f230->f2E; i++) {
        r = CharaRecFindLevelRow_401880(o->f230, i, 0, 0);
        if (r != 0) {
            return r;
        }
    }
    return 0;
}
