#include "types.h"

class A2E7CF0 {
public:
    u8 pad000[0xDC];
};

class Q2E7CF0 : public A2E7CF0 {
public:
    /* +0x008 */ virtual void v008();
    /* +0x00C */ virtual void v00C();
    /* +0x010 */ virtual void v010();
    /* +0x014 */ virtual void v014();
    /* +0x018 */ virtual void v018();
    /* +0x01C */ virtual void v01C();
    /* +0x020 */ virtual void v020();
    /* +0x024 */ virtual void v024();
    /* +0x028 */ virtual void v028();
    /* +0x02C */ virtual void v02C();
    /* +0x030 */ virtual void v030();
    /* +0x034 */ virtual void v034();
    /* +0x038 */ virtual void v038();
    /* +0x03C */ virtual void v03C();
    /* +0x040 */ virtual void v040();
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
