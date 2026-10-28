/* rgp:protos */
#define RGP_SELF_PadIsAnalogMode_184960 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern s32 scePadGetState(s32, s32);
extern s32 scePadInfoMode(s32, s32, s32, s32);
struct Obj0 { u8 pad000[0xB4]; s32 mB4; s32 mB8; };
u8 PadIsAnalogMode_184960(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 r0;
    s32 rv2;
    s32 rv1;
    s32 t2;
    s32 t3;
    s32 r3;
    t0 = p0->mB8;
    t1 = p0->mB4;
    r0 = scePadGetState(t1, t0);
    if (r0 == 6) {
        rv2 = 1;
    } else {
        if (r0 == 2) {
            rv2 = 1;
        } else {
            rv2 = 0;
        }
    }
    if (rv2 == 0) {
        return (u8)0;
    }
    t2 = p0->mB4;
    t3 = p0->mB8;
    r3 = scePadInfoMode(t2, t3, 1, 0);
    return (r3 == 7);
}
