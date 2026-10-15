#include "types.h"

extern s32 DrawListAddTexLoadChecked_140560(s32, s32);
extern s32 DrawListEmitBucketById_140830(s32, s32);
extern s32 GetDrawCtx_15de80(void);
extern s32 SceneTableCollectDrawGroupTexIdsMaybe_1961a0(s32, s32, s32 *, s32);
extern s32 GetCurrentScene_1f5be0(void);

void MapDrawGroupRange_1e1710(s32 arg0, s32 from, s32 to)
{
    s32 k;
    s32 m;
    s32 i;
    s32 j;
    s32 n;
    s32 e;
    s32 buf[0x80];

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
