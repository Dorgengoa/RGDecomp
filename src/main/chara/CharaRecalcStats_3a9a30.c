#include "types.h"

extern void CharaResetStatsToBaseThunk_3a9ad0(void *);
extern s32 CharaApplyStatModsThunk_3a9ab0(void *);

u8 CharaRecalcStats_3a9a30(void *a)
{
    CharaResetStatsToBaseThunk_3a9ad0(a);
    return CharaApplyStatModsThunk_3a9ab0(a);
}
