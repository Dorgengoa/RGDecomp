#include "types.h"
/* normal 0x005069C0 -- sets the list's scroll velocity. */
typedef struct Obj { u8 pad00[0xA8]; f32 fA8; } Obj;
extern void normal_LeaderHudSetWeaponGaugeShown_5069c0(Obj *p, f32 x);
void normal_LeaderHudSetWeaponGaugeShown_5069c0(Obj *p, f32 x)
{
    p->fA8 = x;
}
