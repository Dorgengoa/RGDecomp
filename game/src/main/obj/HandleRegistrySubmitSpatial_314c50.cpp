#include "types.h"

typedef struct {
    s32 m0;
    s32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
    u8 pad14[8];
    void *m1C;
} Out;

class Obj {
public:
    u8 pad0[0x86];
    s16 m86;
    s16 m88;
    s16 m8A;
    u8 pad8C[0xB0 - 0x8C];
    VC_VPTR_MEMBER;
    
    Out * f10(void * a0) { return VCM(Out *, (void *, void *), 0x10, a0); }
    Out * f14(void * a0) { return VCM(Out *, (void *, void *), 0x14, a0); }
    s16 mB4;
};

typedef struct {
    s32 m0;
    Obj **h;
} Elem;

class Sink {
public:
    VC_VPTR_MEMBER;
    
    
    
    void f18(Out * a0, Obj *** a1) { VCM(void, (void *, Out *, Obj ***), 0x18, a0, a1); }
    void f1C(Out * a0, Obj *** a1) { VCM(void, (void *, Out *, Obj ***), 0x1C, a0, a1); }
};

static inline bool isnull(Obj **p) { return !(p != 0); }
static inline Obj *get(Obj **h) { return h ? *h : 0; }

extern "C" void HandleRegistrySubmitSpatial_314c50(Elem *e0, Sink *s) {
    Elem *e;
    s32 i;
    Out *o;

    if (s == 0) {
        return;
    }
    e = e0;
    for (i = 0; i < 0x200; i++, e++) {
        if (isnull(e->h)) {
            continue;
        }
        o = get(e->h)->f10(s);
        if (o != 0) {
            o->m0 = get(e->h)->mB4;
            o->m8 = get(e->h)->m86;
            o->m10 = get(e->h)->m88;
            o->mC = get(e->h)->m8A;
            o->m1C = (u8 *)get(e->h) + 0x10;
            s->f18(o, &e->h);
        }
        o = get(e->h)->f14(s);
        if (o != 0) {
            o->m0 = get(e->h)->mB4;
            o->m8 = get(e->h)->m86;
            o->m10 = get(e->h)->m88;
            o->mC = get(e->h)->m8A;
            s->f1C(o, &e->h);
        }
    }
}
