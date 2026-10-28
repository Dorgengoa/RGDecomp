/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetScrollStep_505d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505D80 -- sets the popup's scroll velocity. */
typedef struct Obj { u8 pad00[0x6C]; f32 f6C; } Obj;
extern void normal_BtlChgPageSetScrollStep_505d80(Obj *p, f32 x);
void normal_BtlChgPageSetScrollStep_505d80(Obj *p, f32 x)
{
    p->f6C = x;
}
