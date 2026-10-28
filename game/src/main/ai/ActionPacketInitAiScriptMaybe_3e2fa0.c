/* rgp:protos */
#define RGP_SELF_ActionPacketInitAiScriptMaybe_3e2fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    u8 m04;
    u8 pad005[0x1F];
    s16 m24;
};

struct Obj0 *ActionPacketInitAiScriptMaybe_3e2fa0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;

    r0 = ((s32)ActionPacketInitBattleDamage_3e3140(p0, p1, p2, p2, 0));
    p0->m04 = 0x43;
    p0->m24 = p3;
    return p0;
}
