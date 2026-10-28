/* rgp:protos */
#define RGP_SELF_NavEdgeSetDirFlag_3115a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003115a0 {
    s16 f00;
    s16 f02;
    u8 pad004[0xA];
    s16 f0E;
    s16 f10;
} Obj_FUN_003115a0;

void NavEdgeSetDirFlag_3115a0(Obj_FUN_003115a0 *o, s32 a, s32 b, u8 v)
{
    if (o->f00 == a && o->f02 == b) {
        o->f0E = v;
    } else if (o->f00 == b && o->f02 == a) {
        o->f10 = v;
    }
}
