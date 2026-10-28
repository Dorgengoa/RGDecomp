/* rgp:protos */
#define RGP_SELF_EffDefCmdWorld_19ef10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Q { u8 pad0[0x38]; s32 f38; } Q;
typedef struct P { u8 pad0[0x28]; Q *f28; } P;

s32 EffDefCmdWorld_19ef10(void *a, s32 b, P **c)
{
    Q *q = (*c)->f28;

    if (q == 0) return 0;
    q->f38 = 1;
    return 1;
}
