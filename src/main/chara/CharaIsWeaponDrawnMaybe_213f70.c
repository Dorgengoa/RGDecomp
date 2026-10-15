#include "types.h"

struct T213F70 { u8 pad000[0xA2E]; s16 fA2E; };

u8 CharaIsWeaponDrawnMaybe_213f70(struct T213F70 *p)
{
    s16 v;
    u8 r;

    v = p->fA2E;
    r = 1;
    if (v == 2) goto ok;
    if (v == 3) goto ok;
    r = 0;
ok:
    return r;
}
