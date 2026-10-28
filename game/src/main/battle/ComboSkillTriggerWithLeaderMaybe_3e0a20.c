/* rgp:protos */
#define RGP_SELF_ComboSkillTriggerWithLeaderMaybe_3e0a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct U3E0A20 { u8 pad000[0x18E]; s16 f18E; };
struct T3E0A20 { u8 pad000[0x18]; struct U3E0A20 *f18; };

extern struct T3E0A20 *D_00483990;
/*rgp*/

s32 ComboSkillTriggerWithLeaderMaybe_3e0a20(s32 a0)
{
    struct T3E0A20 *g;

    g = D_00483990;
    if (g == 0) {
        return 0;
    }
    return ComboSkillTriggerMaybe_3e0a50(a0, g->f18->f18E);
}
