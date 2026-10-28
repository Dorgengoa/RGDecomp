/* rgp:protos */
#define RGP_SELF_EntryScriptCmdSetBlockPos_3227d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x24];
    s16 m24;
    s16 m26;
    u8 pad028[0x4];
    s16 m2C;
    s16 m2E;
};

s32 EntryScriptCmdSetBlockPos_3227d0(s32 p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;
    E8W *q;

    q = (E8W *)p0;
    r0 = GetEntryTableGlobal_32c2e0();
    if (r0 == 0) {
        return 0;
    }
    r1 = VariantGetInt_15f780((s32)q++);
    r2 = VariantGetInt_15f780((s32)q);
    r0->m24 = r1;
    r0->m26 = r2;
    r0->m2C = 0;
    r0->m2E = 0;
    return 1;
}
