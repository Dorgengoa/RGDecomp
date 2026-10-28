#include "types.h"

class IBase {
public:
    u8 pad000[0xDC];
};

class Inner : public IBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void v5(void *arg) { VCM(void, (void *, void *), 0x1C, arg); }
};

typedef struct L16 { u8 b[0x10]; } L16;

struct Owner {
    u8  pad000[0x50];
    L16 list[0x10];
};

struct Node {
    u8 pad000[0x10];
};

extern "C" Node *DListGetHead_42ea60(L16 *l);
extern "C" Node *DListGetNext_42eb30(Node *n);

extern "C" void EventObjMgrNotifyAreaLoaded_2e87b0(Owner *o, void *arg)
{
    s32   i;
    Node *q;

    for (i = 0; i < 0x10; i++) {
        q = DListGetHead_42ea60(&o->list[i]);
        while (q != 0) {
            ((Inner *)((u8 *)q + 0x10))->v5(arg);
            q = DListGetNext_42eb30(q);
        }
    }
}
