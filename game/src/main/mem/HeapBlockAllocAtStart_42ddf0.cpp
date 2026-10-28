#include "types.h"

struct Hdr {
    u32 size;
    u32 flags;
    void *owner;
    u32 pad;
    void Clear() {
        flags = 0;
        size = 0;
        owner = 0;
    }
};

struct Block {
    u8 pad0[0x10];
    Hdr h;
};

class CbBase {
public:
    s32 m0;
    s32 m4;
    s32 m8;
};

class Cb : public CbBase {
public:
    VC_VPTR_MEMBER; void Free(s32 a0, void * a1, s32 a2) { VCM(void, (void *, s32, void *, s32), 0x8, a0, a1, a2); }
    void Alloc(s32 a0, void * a1, s32 a2) { VCM(void, (void *, s32, void *, s32), 0xC, a0, a1, a2); }
    bool Ready() { return m0 != 0 && m4 != 0; }
};

extern "C" Block *PtrAdd_42e2f0(void *, u32);
extern "C" void HeapBlockLinkAfter_42e6f0(s32, Block *, Block *);
extern "C" void DListNodeInit_42ec10(Block *);

extern "C" void *HeapBlockAllocAtStart_42ddf0(s32 a0, Block *b, s32 n, Cb *cb)
{
    Hdr *h;
    u32 size;
    u32 rem;
    Block *p;
    Hdr *ph;

    if (b == 0) {
        return 0;
    }
    h = &b->h;
    h->flags |= 2;
    h->flags &= ~1;
    h->owner = cb;
    if (cb != 0) {
        if (cb->Ready()) {
            cb->Alloc(a0, h + 1, n);
        } else {
            cb->Free(a0, h + 1, n);
        }
    }
    size = (n + 0xF) & ~0xF;
    rem = b->h.size - size;
    if (rem > 0x20) {
        h->size = size;
        p = PtrAdd_42e2f0(h + 1, size);
        ph = &p->h;
        DListNodeInit_42ec10(p);
        p->h.Clear();
        ph->size = rem - 0x20;
        ph->flags = 0;
        HeapBlockLinkAfter_42e6f0(a0, b, p);
    }
    return h + 1;
}
