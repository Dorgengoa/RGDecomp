/* rgp:protos */
#define RGP_SELF_SoundThreadCmd13Related_1b6a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

/*rgp*/

void SoundThreadCmd13Related_1b6a30(struct Obj0 *p0)
{
    SoundIopSendCmdG2S3_165d28(p0->m00, p0->m04);
}
