/* rgp:protos */
#define RGP_SELF_MapDrawGroupRange_1e1710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapDrawGroupRange_1e1710(s32 arg0, s32 from, s32 to)
{
    s32 k;
    s32 m;
    s32 i;
    s32 j;
    s32 n;
    s32 e;
    s32 buf[0x80] __attribute__((aligned(16)));

    k = GetCurrentScene_1f5be0();
    m = GetDrawCtx_15de80();
    for (i = from; i <= to; i++) {
        n = SceneTableCollectDrawGroupTexIdsMaybe_1961a0(k + 0x4020, i, buf, 0x80);
        for (j = 0; j < n; j++) {
            e = buf[n - j - 1];
            if (DrawListAddTexLoadChecked_140560(m, e)) {
                DrawListEmitBucketById_140830(m, e);
            }
        }
    }
}
