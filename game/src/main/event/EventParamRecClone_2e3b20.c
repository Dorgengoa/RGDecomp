/* rgp:protos */
#define RGP_SELF_EventParamRecClone_2e3b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_002e3b20 {
    u8 pad0[0x10];
    f32 f10;
    f32 f14;
    f32 f18;
} S_002e3b20;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EventParamRecClone_2e3b20(S_002e3b20 *self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    EventParamRecReset_2e3c50(self);
    if (p2 == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    if (EventRecClone_2e5740(self, p1, p2, p3, p4, p5) == 0) return 0;
    self->f10 = EventParamRecGetSpring_2e3b10(p2);
    self->f14 = EventParamRecGetDamping_2e3b00(p2);
    self->f18 = EventParamRecGetLimit_2e3af0(p2);
    return 1;
}
