/* rgp:protos */
#define RGP_SELF_EvCmdVoiceProtectLastChan_245ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E7E8;
extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EvCmdVoiceProtectLastChan_245ca0(s32 p0)
{
    s32 r0;
    s32 t0;
    struct Obj0 * t1;
    s32 t2;

    r0 = ScriptGetInt_2490f0(p0);
    t0 = D_0047E7E8;
    t1 = gEventContext;
    t2 = gEventContext->m04;
    EventVoiceChanSetProtected_24e740((t2 + 0x420), t0, (r0 != 0), 0, 0);
    return 1;
}
