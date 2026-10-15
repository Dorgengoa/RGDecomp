#include "types.h"

class VE2E88C0 {
public:
    u8 pad000[0xDC];
    virtual void d0();
    virtual void d1();
    virtual void v2(s32 a);
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void v8(void);
};
extern "C" void *DListGetHead_42ea60(s32);
extern "C" void *DListGetNext_42eb30(void *);

extern "C" void EventObjMgrResolveAndResetAll_2e88c0(s32 arg0)
{
    s32 var_17;
    u8 *var_2;

    var_17 = 0;
    do {
        var_2 = (u8 *)DListGetHead_42ea60(arg0 + (var_17 * 0x10) + 0x50);
        while (var_2 != NULL) {
            ((VE2E88C0 *)(var_2 + 0x10))->v2(0);
            ((VE2E88C0 *)(var_2 + 0x10))->v8();
            var_2 = (u8 *)DListGetNext_42eb30(var_2);
            continue;
        }
        var_17 += 1;
    } while (var_17 < 0x10);
}
