/* rgp:protos */
#define RGP_SELF_EvTargetSphereInVolumes_352740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 m[4]; } M_00352740;

/*rgp*/
/*rgp*/

s32 EvTargetSphereInVolumes_352740(void *a, void *b, void *c, f32 v)
{
    M_00352740 m __attribute__((aligned(16)));

    if (c == 0) return 0;
    XformToLocal_2e7440((void *)((s32)a + 0x80), &m, b);
    return EventVolumeRecAnyHitTrainWarp_2e4ab0(c, &m, v);
}
