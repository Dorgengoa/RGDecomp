#include "types.h"

struct Rec_003352A0 {
    s32 f00;
    u8 f04;
    u8 pad005[0x3];
};

class C_003352A0 {
    u8 pad000[0xDC];
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02C */ 
    /* +0x030 */ void v30(Rec_003352A0 *r) { VCM(void, (void *, Rec_003352A0 *), 0x30, r); }
    /* +0x034 */ void v34(Rec_003352A0 *r) { VCM(void, (void *, Rec_003352A0 *), 0x34, r); }
};

extern "C" void EvObjLiftSnapClosed_335b50(C_003352A0 *o, s32 i);

extern "C" void EvObjLiftApplyInitialState_3352a0(C_003352A0 *o)
{
    Rec_003352A0 r __attribute__((aligned(16)));
    s32 i;

    r.f00 = 0;
    r.f04 = 0;
    for (i = 0; i < *(s16 *)((u8 *)o + 0xEA); i++) {
        EvObjLiftSnapClosed_335b50(o, i);
        o->v30(&r);
        o->v34(&r);
    }
}
