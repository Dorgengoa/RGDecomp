/* rgp:protos */
#define RGP_SELF_WorldDataTableClearHook_3b8d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_func_003B8D20 {
    u8 pad000[0x9A];
    u8 b9A_0 : 1;
    u8 b9A_1 : 1;
    u8 b9A_2 : 1;
    u8 b9A_r : 5;
    u8 pad09B[0x1];
    s16 f9C;
    s16 f9E;
    s16 fA0;
} Obj_func_003B8D20;

void WorldDataTableClearHook_3b8d20(Obj_func_003B8D20 *o)
{
    o->b9A_1 = 0;
    o->b9A_2 = 0;
    o->f9C = -1;
    o->f9E = 0;
    o->fA0 = 0;
}
