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

struct Mgr {
    u8 pad0[4];
    u8 m4[0x7c];
    s32 m80;
    u8 pad84[0xc];
    List **m90;
};

extern "C" void MemStackClear_14dff0(void *);

extern "C" void SpatialGridClear_316940(Mgr *m)
{
    List **pp;
    s32 i;
    Node *n;
    Node *next;
    List *l;

    pp = m->m90;
    if (pp != 0) {
        for (i = 0; i < m->m80; i++, pp++) {
            if (*pp != 0) {
                l = *pp;
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
                *pp = 0;
            }
        }
    }
    MemStackClear_14dff0(m->m4);
}
