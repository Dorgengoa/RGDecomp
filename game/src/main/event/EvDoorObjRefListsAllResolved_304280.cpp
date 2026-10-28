/* rgp:protos */
#line 1
#include "types.h"

class C_00304280 {
    u8 pad000[0xDC];
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ s32 v14(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x14, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 EventRefListAllResolved_304890(s32 *p);

extern "C" s32 EvDoorObjRefListsAllResolved_304280(C_00304280 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 i;
    s32 *base;

    if (o->v14((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)((u8 *)o + 0x188); i++) {
        base = *(s32 **)((u8 *)o + 0x180);
        if (EventRefListAllResolved_304890(base + i * 3) == 0) {
            return 0;
        }
    }
    return 1;
}
