#include "types.h"
/* normal 0x005069F0 -- clamp the scroll velocity at zero; the `bc1fl` delay
 * slot carries the else-branch store. */
typedef struct Obj { u8 pad00[0xA0]; f32 fA0; } Obj;
extern s32 normal_LeaderHudSetWeaponFlash_5069f0(Obj *p, f32 x);
s32 normal_LeaderHudSetWeaponFlash_5069f0(Obj *p, f32 x)
{
    if (x < 0.0f) {
        p->fA0 = 0.0f;
        return 1;
    }
    p->fA0 = x;
    return 0;
}
