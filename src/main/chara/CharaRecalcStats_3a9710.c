#include "types.h"

extern void CharaResetStatsToBaseThunk_3a97b0(void *);
extern s32 CharaApplyStatModsThunk_3a9790(void *);

u8 CharaRecalcStats_3a9710(void *a)
{
    CharaResetStatsToBaseThunk_3a97b0(a);
    return CharaApplyStatModsThunk_3a9790(a);
}
