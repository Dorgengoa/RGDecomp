#include "types.h"

extern void CharaResetStatsToBaseThunk_3a9600(void *);
extern s32 CharaApplyStatModsThunk_3a95e0(void *);

u8 CharaRecalcStats_3a9560(void *a)
{
    CharaResetStatsToBaseThunk_3a9600(a);
    return CharaApplyStatModsThunk_3a95e0(a);
}
