#include "types.h"

struct Rec_003352A0 {
    s32 f00;
    u8 f04;
    u8 pad005[0x3];
};

class C_003352A0 {
    u8 pad000[0xDC];
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void s010();
    /* +0x014 */ virtual void s014();
    /* +0x018 */ virtual void s018();
    /* +0x01C */ virtual void s01C();
    /* +0x020 */ virtual void s020();
    /* +0x024 */ virtual void s024();
    /* +0x028 */ virtual void s028();
    /* +0x02C */ virtual void s02C();
    /* +0x030 */ virtual void v30(Rec_003352A0 *r);
    /* +0x034 */ virtual void v34(Rec_003352A0 *r);
};

extern "C" void EvObjLiftSnapClosed_335b50(C_003352A0 *o, s32 i);

extern "C" void EvObjLiftApplyInitialState_3352a0(C_003352A0 *o)
{
    Rec_003352A0 r;
    s32 i;

    r.f00 = 0;
    r.f04 = 0;
    for (i = 0; i < *(s16 *)((u8 *)o + 0xEA); i++) {
        EvObjLiftSnapClosed_335b50(o, i);
        o->v30(&r);
        o->v34(&r);
    }
}
