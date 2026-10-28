#include "types.h"

class ObjB {
public:
    u8 pad0[0xb0];
};

class Obj : public ObjB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Kill(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
};

struct Ref {
    Obj *obj;
    s32 count;
};

struct Node {
    Ref *ref;
    u8 pad4[4];
    Node *next;
    bool IsValid() { return ref != 0; }
    bool IsInvalid() { return !IsValid(); }
    void Dec() { if (ref != 0) ref->count--; }
    s32 Count() { if (ref != 0) return ref->count; return 0; }
    void Free() {
        if (ref != 0) {
            if (ref->obj != 0) {
                ref->obj->Kill(-1);
            }
            ref->count = 0;
            ref = 0;
        }
    }
    void Release() {
        bool b = !IsValid();
        if (b) return;
        Dec();
        if (Count() == 0) {
            Free();
        }
        ref = 0;
    }
};

struct List {
    Node *head;
};

struct Sub {
    u8 pad0[0x14];
    s32 m14[4];
    u8 m24[4];
};

struct Mgr {
    u8 pad0[4];
    u8 m4[0x90];
    List *m94;
    Sub *m98;
};

extern "C" void MemStackClear_14dff0(void *);
extern "C" void QuadTreeNodeDtor_316050(s32, s32);
extern "C" void QuadTreeItemListDtor_315ad0(void *, s32);

extern "C" void SpatialMgrClear_315f20(Mgr *m)
{
    Node *n;
    Node *next;
    List *l;
    Sub *p;
    s32 i;

    l = m->m94;
    if (l != 0) {
        if (l != 0) {
            n = l->head;
            while (n != 0) {
                next = n->next;
                if (n != 0) {
                    if (n != 0) n->Release();
                }
                n = next;
            }
        }
    }
    p = m->m98;
    if (p != 0) {
        if (p != 0) {
            i = 0;
            do {
                QuadTreeNodeDtor_316050(p->m14[i], -1);
                i++;
            } while (i < 4);
            QuadTreeItemListDtor_315ad0(p->m24, -1);
        }
    }
    MemStackClear_14dff0(m->m4);
}
