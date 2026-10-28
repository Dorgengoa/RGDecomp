#include "types.h"

class A2E7CF0 {
public:
    u8 pad000[0xDC];
};

class Q2E7CF0 : public A2E7CF0 {
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
    /* +0x03C */ 
    /* +0x040 */ void v040() { VCM0(void, 0x40); }
};

struct E2E7CF0 {
    u8 pad000[0x10];
    Q2E7CF0 q;
};

extern "C" E2E7CF0 *DListGetHead_42ea60(void *);
extern "C" E2E7CF0 *DListGetNext_42eb30(E2E7CF0 *);
extern "C" void EventObjMgrPreUpdateAllMaybe_2e8440(void *);
extern "C" void EventObjMgrUpdateAll_2e8290(void *);

extern "C" void EventObjMgrResumeAll_2e7cf0(void *self)
{
    s32 i;
    E2E7CF0 *p;

    for (i = 0; i < 0x10; i++) {
        p = DListGetHead_42ea60((u8 *)self + i * 16 + 0x50);
        while (p != 0) {
            p->q.v040();
            p = DListGetNext_42eb30(p);
        }
    }
    EventObjMgrPreUpdateAllMaybe_2e8440(self);
    EventObjMgrUpdateAll_2e8290(self);
}
