/* rgp:protos */
#define RGP_SELF_normal_LeaderHudActivate_506d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506D80 -- the 0x5C store rides the first `jal`'s delay slot. */
typedef struct Obj { u8 pad00[0x5C]; s8 f5C; } Obj;
/*rgp*/
/*rgp*/
extern s32 normal_LeaderHudActivate_506d80(Obj *p);
s32 normal_LeaderHudActivate_506d80(Obj *p)
{
    p->f5C = 1;
    normal_LeaderHudSetBannerPhase_506b30(p, 0);
    normal_LeaderHudSetWeaponGaugeShown_5069c0(p, 0.0f);
    return 1;
}
