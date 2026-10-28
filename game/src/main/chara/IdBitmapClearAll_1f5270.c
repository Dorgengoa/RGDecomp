/* rgp:protos */
#define RGP_SELF_IdBitmapClearAll_1f5270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_001f5270 {
    u8 pad000[0x4];
    u8 *f04;
    s32 f08;
} Obj_FUN_001f5270;

void IdBitmapClearAll_1f5270(Obj_FUN_001f5270 *o)
{
    s32 i;

    for (i = 0; i < o->f08 / 8; i++) {
        o->f04[i] = 0;
    }
}
