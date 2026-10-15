#include "types.h"

extern void CharaResetStatsToBaseThunk_3a9950(void *);
extern s32 CharaApplyStatModsThunk_3a9930(void *);

u8 CharaRecalcStats_3a98b0(void *a)
{
    CharaResetStatsToBaseThunk_3a9950(a);
    return CharaApplyStatModsThunk_3a9930(a);
}
