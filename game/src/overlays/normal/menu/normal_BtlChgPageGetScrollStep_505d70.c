/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageGetScrollStep_505d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505D70 -- leaf float accessor, +0x6C. */

typedef struct Ctx { u8 pad000[0x6C]; f32 f06C; } Ctx;

f32 normal_BtlChgPageGetScrollStep_505d70(Ctx *p)
{
    return p->f06C;
}
