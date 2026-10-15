#include "types.h"

extern void UnitResetStatsToBaseThunk_3bc460(void *);
extern s32 UnitApplyStatusStatModsThunk_3bc440(void *);

u8 UnitRecalcStats_3bc3c0(void *a)
{
    UnitResetStatsToBaseThunk_3bc460(a);
    return UnitApplyStatusStatModsThunk_3bc440(a);
}
