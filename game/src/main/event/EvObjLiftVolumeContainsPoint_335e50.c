/* rgp:protos */
#define RGP_SELF_EvObjLiftVolumeContainsPoint_335e50 1
#define RGP_SELF_alive 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
typedef struct { u8 pad0[0x10]; u8 v10[0x90]; u8 vA0[0x30]; u32 D0; u8 padD4[0x18]; s32 EC; } O;
static inline s32 alive(O *p) { return !((p->D0 & 0x80000000) != 0); }

s32 EvObjLiftVolumeContainsPoint_335e50(O *arg0, s32 arg1)
{
    u8 sp30[0x10] __attribute__((aligned(16)));

if (!(alive(arg0))) {
return 0;
}
if (!(arg0->D0 & 0x02000000)) {
return 0;
}
if (!(TargetRefIsActive_2e6f00(arg0->vA0) != 0)) {
return 0;
}
if (!(arg0->EC != 0)) {
return 0;
}
XformToLocal_2e7440(arg0->v10, sp30, arg1);
return EventVolumeRecAnyHit_2e4c70(arg0->EC, sp30, 0.0f);
}
