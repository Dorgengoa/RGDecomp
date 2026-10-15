#include "types.h"

extern void UnitResetStatsToBaseThunk_3bc6e0(void *);
extern s32 UnitApplyStatusStatModsThunk_3bc6c0(void *);

u8 UnitRecalcStats_3bc640(void *a)
{
    UnitResetStatsToBaseThunk_3bc6e0(a);
    return UnitApplyStatusStatModsThunk_3bc6c0(a);
}
