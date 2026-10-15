#include "types.h"

class VE2E8840 {
public:
    u8 pad000[0xDC];
    virtual void d0();
    virtual void d1();
    virtual void v2(s32);
};

extern "C" void *DListGetHead_42ea60(s32);
extern "C" void *DListGetNext_42eb30(void *);

extern "C" void EventObjMgrResolveAllTargets_2e8840(s32 arg0)
{
    s32 i;
    u8 *p;

    i = 0;
    do {
        p = (u8 *)DListGetHead_42ea60(arg0 + (i * 0x10) + 0x50);
        while (p != NULL) {
            ((VE2E8840 *)(p + 0x10))->v2(0);
            p = (u8 *)DListGetNext_42eb30(p);
        }
        i += 1;
    } while (i < 0x10);
}
