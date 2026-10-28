/* rgp:protos */
#define RGP_SELF_ObjTypeMonographSetMagnetOffTime_372730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T372730 { u8 pad000[0xD0]; u32 fD0; u8 pad0D4[0x24]; f32 fF8; };

void ObjTypeMonographSetMagnetOffTime_372730(struct T372730 *p, f32 x)
{
    s32 ok;

    ok = !(p->fD0 & 0x80000000);
    if (ok) {
        p->fF8 = x;
    }
}
