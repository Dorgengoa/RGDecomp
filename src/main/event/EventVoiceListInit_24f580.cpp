#include "types.h"

class VN;

class VC {
public:
    u8 pad[0x34];
    virtual void v08();
};

extern "C" {
extern void *MemStackNew_14e230(s32, s32);
extern void *memset(void *, s32, u32);
extern u8 D_00471498[];
}

class VN {
public:
    VN *next;
    VN *prev;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x34 - 0x10];
    void *vp;
    VN() {
        vp = D_00471498;
        memset(&unk10(), 0, 0x24);
        ((VC *)this)->v08();
    }
    u8 &unk10() { return pad10[0]; }
    void *operator new(u32 sz, s32 a) { return MemStackNew_14e230(sz, a); }
};

struct NL {
    VN *head;
    s32 unk4;
    s32 unk8;
    void add(VN *n) {
        VN *p;
        unk4 = 0;
        unk8 = 0;
        p = head;
        if (p != 0) {
            while (p != 0) {
                if (p->next == 0) break;
                p = p->next;
            }
            p->next = n;
            if (n != 0) n->prev = p;
        } else {
            head = n;
        }
    }
};

extern "C" void EventVoiceListInit_24f580(NL *arg0, s32 arg1)
{
    VN *n;

    n = new (arg1) VN;
    if (n != 0) {
        n->unkC = 1;
        n->unk8 = 0;
        arg0->add(n);
    }
    n = new (arg1) VN;
    if (n != 0) {
        n->unkC = 2;
        n->unk8 = 0;
        arg0->add(n);
    }
}
