/* rgp:protos */
#define RGP_SELF_WorldDataRequestInit_3f4060 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct S3f4060 {
    s16 m00; s16 m02; s16 m04; u8 pad006[2];
    s32 m08; s32 m0C; s32 m10;
    u8 b0 : 1; u8 rest : 7;
};

void WorldDataRequestInit_3f4060(struct S3f4060 *p)
{
    p->m00 = -1;
    p->m04 = -1;
    p->m02 = 0;
    p->m08 = -1;
    p->m0C = 0;
    p->m10 = 0;
    p->b0 = 0;
}
