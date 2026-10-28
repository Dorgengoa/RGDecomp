/* rgp:protos */
#line 1
#include "types.h"

class VE2E88C0 {
public:
    u8 pad000[0xDC];
    VC_VPTR_MEMBER;
    
    void v2(s32 a) { VCM(void, (void *, s32), 0x10, a); }
    
    
    
    
    
    void v8() { VCM0(void, 0x28); }
};
extern "C" void * DListGetHead_42ea60(s32);
extern "C" void * DListGetNext_42eb30(void *);

extern "C" int EventObjMgrResolveAndResetAll_2e88c0(s32 arg0)
{ int rgp_v0 = 0;
    s32 var_17;
    u8 *var_2;

    var_17 = 0;
    do {
        var_2 = (u8 *)(rgp_v0 = (int)(long)(DListGetHead_42ea60(arg0 + (var_17 * 0x10) + 0x50)));
        while (var_2 != NULL) {
            ((VE2E88C0 *)(var_2 + 0x10))->v2(0);
            ((VE2E88C0 *)(var_2 + 0x10))->v8();
            var_2 = (u8 *)(rgp_v0 = (int)(long)(DListGetNext_42eb30(var_2)));
            continue;
        }
        var_17 += 1;
    } while (var_17 < 0x10);
return rgp_v0; }
