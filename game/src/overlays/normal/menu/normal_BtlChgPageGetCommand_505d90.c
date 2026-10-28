/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageGetCommand_505d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505D90 -- leaf signed-byte accessor, +0x71 (`lb`). */

typedef struct Ctx { u8 pad000[0x71]; s8 f071; } Ctx;

s32 normal_BtlChgPageGetCommand_505d90(Ctx *p)
{
    return p->f071;
}
