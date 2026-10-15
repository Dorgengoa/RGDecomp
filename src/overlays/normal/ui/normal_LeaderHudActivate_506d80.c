#include "types.h"
/* normal 0x00506D80 -- the 0x5C store rides the first `jal`'s delay slot. */
typedef struct Obj { u8 pad00[0x5C]; s8 f5C; } Obj;
extern s32  normal_LeaderHudSetBannerPhase_506b30(void *p, s8 v);
extern void normal_LeaderHudSetWeaponGaugeShown_5069c0(void *p, f32 x);
extern s32 normal_LeaderHudActivate_506d80(Obj *p);
s32 normal_LeaderHudActivate_506d80(Obj *p)
{
    p->f5C = 1;
    normal_LeaderHudSetBannerPhase_506b30(p, 0);
    normal_LeaderHudSetWeaponGaugeShown_5069c0(p, 0.0f);
    return 1;
}
