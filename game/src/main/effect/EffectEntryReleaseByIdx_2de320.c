/* rgp:protos */
#define RGP_SELF_EffectEntryReleaseByIdx_2de320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_002de320;

/*rgp*/

void EffectEntryReleaseByIdx_2de320(void *base, V_002de320 *src)
{
    V_002de320 v __attribute__((aligned(16)));
    s32 i;

    v = *src;
    i = *(s32 *)&v.y;
    if (i < 0 || i >= 0x30) return;
    EffectEntryReleaseFull_2da420((void *)((s32)base + i * 224));
}
