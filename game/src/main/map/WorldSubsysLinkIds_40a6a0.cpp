/* rgp:protos */
#line 1
#include "types.h"

extern "C" void *IterNext_370040(void *);
extern "C" void IterInit_370170(void *, void *, int, int);

class V {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v70(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};
struct H { u8 pad[8]; V *v; };
struct Ent { s32 m0; s32 m4; s32 m8; s32 mC; s32 *m10; };
struct Obj { u8 pad[0x5c]; H *h5c; u8 pad60[8]; H *h68; };

class Iter {
    u8 d[8];
public:
    Iter(void *b) { IterInit_370170(this, b, 0, 0); }
    Ent *next() { return (Ent *)IterNext_370040(this); }
};
inline s32 conv(H *h, s16 x) { return h->v->v70(x); }
extern "C" s32 WorldSubsysLinkIds_40a6a0(u8 *arg0, Obj *arg1) {
    Ent *e;
    s32 *p;
    s32 i;

    if (arg1 == 0) return 0;
    u8 *b = arg0;
    if (b) b += 0x88;
    Iter it(b);
    while ((e = it.next()) != 0) {
        e->m4 = arg1->h68->v->v70(e->m4);
        if ((s16)e->mC > 0) {
            p = e->m10;
            if (p != 0) {
                for (i = 0; i < (s16)e->mC; i++, p++) {
                    *p = arg1->h5c->v->v70(*p);
                }
            }
        }
    }
    return 1;
}
