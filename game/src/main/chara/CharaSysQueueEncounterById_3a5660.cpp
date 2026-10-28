/* rgp:protos */
#line 1
#pragma opt_propagation off
#pragma opt_common_subs off
#include "types.h"
#undef NULL
#define NULL 0
class Lookup { public:
VC_VPTR_MEMBER;

























s32 get(s64 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s64, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

struct Bits{u8 b0:1;u8 b1:1;u8 b2:1;};
extern "C" {

extern s32 GameReqQueueRemoveById_1f5a10(s32);
extern s32 GameReqQueuePushBack_1f5b50(s32, s32);
extern void *D_004837C0;
extern void *D_004837C4;

s32 CharaSysQueueEncounterById_3a5660(void *arg0, s64 arg1, s32 arg2, int rgp_a3)
{
    s32 result;
    void *p20;
    void *p70;
    void **temp_4;
    void *vt;
    s32 (*fn70)(void *, s64);

    void *g0=D_004837C0; void *g1;
    if (g0==NULL || (g1=D_004837C4)==NULL) return 0;
    p20 = *(void **)((u8 *)g0 + 0x20);
    if (((Bits *)((u8 *)p20+0x24C))->b0) {
        return 0;
    }
    if (((Bits *)((u8 *)arg0+4))->b2 == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x18) != 0) {
        return 0;
    }
    p70 = *(void **)((u8 *)g1 + 0x70);
    temp_4 = *(void ***)((u8 *)p70 + 0x10);
    result=((Lookup *)temp_4)->get((s64)(s16)arg1, (int)(long)(arg2), (int)(long)(rgp_a3));
    if(result==0) return 0;
    {
        *(s32 *)((u8 *)arg0 + 0x18) = result;
        *(s32 *)((u8 *)arg0 + 0x1C) = arg2;
        GameReqQueueRemoveById_1f5a10(7);
        GameReqQueuePushBack_1f5b50(7, 1);
        return 1;
    }
}

}
