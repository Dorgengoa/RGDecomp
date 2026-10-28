/* rgp:protos */
#define RGP_SELF_ViBufFlush_1d3dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void WaitSema(s32);
extern void SignalSema(s32);

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    u8 pad018[0x28];
    s32 m40;
};

void ViBufFlush_1d3dd0(struct Obj0 *p0)
{
    WaitSema(p0->m40);
    p0->m14 = ((p0->m14 + 0x7FF) / 0x800) * 0x800;
    SignalSema(p0->m40);
}
