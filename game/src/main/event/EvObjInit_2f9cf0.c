/* rgp:protos */
#define RGP_SELF_EvObjInit_2f9cf0 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvObjInit_2f9cf0(S_002e3b20 *self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    EvObjReset_2f9eb0(self);
    if (p2 == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    if (EventRecClone_2e5740(self, p1, p2, p3, p4, p5) == 0) return 0;
    if (TargetRefCopy_2e7140((u8 *)self+0xA0,((s32)EvObjGetTargetRef_2f9ca0(p2)),p3)==0) return 0;
    *(s32 *)((u8 *)self+0xD8)=EvObjGetScriptList_2f9c80(p2);
    *(s32 *)((u8 *)self+0xD0)=EvObjGetFlags_2f9ce0(p2);
    return 1;
}
