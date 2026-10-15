#include "types.h"

extern void UnitResetStatsToBaseThunk_3bc5a0(void *);
extern s32 UnitApplyStatusStatModsThunk_3bc580(void *);

u8 UnitRecalcStats_3bc500(void *a)
{
    UnitResetStatsToBaseThunk_3bc5a0(a);
    return UnitApplyStatusStatModsThunk_3bc580(a);
}
