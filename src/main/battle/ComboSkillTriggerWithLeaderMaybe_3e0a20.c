#include "types.h"

struct U3E0A20 { u8 pad000[0x18E]; s16 f18E; };
struct T3E0A20 { u8 pad000[0x18]; struct U3E0A20 *f18; };

extern struct T3E0A20 *D_00483990;
extern s32 ComboSkillTriggerMaybe_3e0a50(s32, s32);

s32 ComboSkillTriggerWithLeaderMaybe_3e0a20(s32 a0)
{
    struct T3E0A20 *g;

    g = D_00483990;
    if (g == 0) {
        return 0;
    }
    return ComboSkillTriggerMaybe_3e0a50(a0, g->f18->f18E);
}
