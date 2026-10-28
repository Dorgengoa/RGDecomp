#include "types.h"

class A2E7D80 {
public:
    u8 pad000[0xDC];
};

class Q2E7D80 : public A2E7D80 {
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
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03C */ void v03C() { VCM0(void, 0x3C); }
    /* +0x040 */ 
};

struct E2E7D80 {
    u8 pad000[0x10];
    Q2E7D80 q;
};

extern "C" E2E7D80 *DListGetHead_42ea60(void *);
extern "C" E2E7D80 *DListGetNext_42eb30(E2E7D80 *);
extern "C" void EventObjMgrPreUpdateAllMaybe_2e8440(void *);
extern "C" void EventObjMgrUpdateAll_2e8290(void *);

extern "C" void EventObjMgrSuspendAll_2e7d80(void *self)
{
    s32 i;
    E2E7D80 *p;

    for (i = 0; i < 0x10; i++) {
        p = DListGetHead_42ea60((u8 *)self + i * 16 + 0x50);
        while (p != 0) {
            p->q.v03C();
            p = DListGetNext_42eb30(p);
        }
    }
    EventObjMgrPreUpdateAllMaybe_2e8440(self);
    EventObjMgrUpdateAll_2e8290(self);
}
