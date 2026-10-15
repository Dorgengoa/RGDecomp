#include "types.h"

extern void CharaResetStatsToBaseThunk_3a9480(void *);
extern s32  CharaApplyStatModsThunk_3a9460(void *);

u8 CharaRecalcStats_3a93e0(void *p)
{
    CharaResetStatsToBaseThunk_3a9480(p);
    return (u8)CharaApplyStatModsThunk_3a9460(p);
}
