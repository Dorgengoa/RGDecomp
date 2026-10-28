/* rgp:protos */
#define RGP_SELF_ItemReset_3d50d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003d50d0 {
    u8 pad000[0x4];
    s16 f04;
    s16 f06;
    s16 f08;
    u8 b0A_0 : 1;
    u8 b0A_1 : 1;
    u8 b0A_r : 6;
    u8 pad00B[0x5];
    s32 f10;
} Obj_FUN_003d50d0;

void ItemReset_3d50d0(Obj_FUN_003d50d0 *o)
{
    o->f04 = -1;
    o->f06 = -1;
    o->f10 = 0;
    o->f08 = 0;
    o->b0A_0 = 0;
    o->b0A_1 = 1;
}
