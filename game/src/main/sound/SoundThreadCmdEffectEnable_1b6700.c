/* rgp:protos */
#define RGP_SELF_SoundThreadCmdEffectEnable_1b6700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void sceSdRemote_1229e8(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

s32 SoundThreadCmdEffectEnable_1b6700(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m00;
    t1 = p0->m04;
    if (t0 != 0) {
        if (t1 != 0) {
            sceSdRemote_1229e8(1, 0x8010, 0x800, -4);
            sceSdRemote_1229e8(1, 0x8010, 0x801, -4);
        } else {
            sceSdRemote_1229e8(1, 0x8010, 0x800, -0x34);
            sceSdRemote_1229e8(1, 0x8010, 0x801, -0x34);
        }
        sceSdRemote_1229e8(1, 0x8070, 2, 1);
        sceSdRemote_1229e8(1, 0x8070, 3, 1);
    } else {
        sceSdRemote_1229e8(1, 0x8010, 0x800, -0x34);
        sceSdRemote_1229e8(1, 0x8010, 0x801, -0x34);
        sceSdRemote_1229e8(1, 0x8070, 2, 0);
        sceSdRemote_1229e8(1, 0x8070, 3, 0);
    }
    return 0;
}
