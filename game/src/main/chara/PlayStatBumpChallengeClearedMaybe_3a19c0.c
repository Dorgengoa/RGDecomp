/* rgp:protos */
#define RGP_SELF_PlayStatBumpChallengeClearedMaybe_3a19c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct G_FUN_003a19c0 {
    u8 pad000[0x10];
    s32 m10;
} G_FUN_003a19c0;

extern G_FUN_003a19c0 *D_004837C0;
/*rgp*/

s32 PlayStatBumpChallengeClearedMaybe_3a19c0(s32 base, s32 i)
{
    s32 k;
    s32 t;
    s32 u;
    u16 *q;

    if (i <= 0 || i > 4) return 0;
    k = StateGetChapterIndexMaybe_3cd500(D_004837C0->m10);
    t = k * 8 - (-base);
    q = (u16 *)(i * 2 - (0 - (s32)t));
    q[0x435] = q[0x435] + 1;
    return 1;
}
