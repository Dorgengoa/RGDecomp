/* rgp:protos */
#line 1
#include "types.h"

struct It { u8 b[0x8]; };
struct A { u8 b[0x18]; };
struct X { u8 pad000[0x88]; };
struct D : X, A { };

class V {
public:
    /* +0x08 */ VC_VPTR_MEMBER;
    /* +0x0C */ 
    /* +0x10 */ 
    /* +0x14 */ 
    /* +0x18 */ 
    /* +0x1C */ 
    /* +0x20 */ 
    /* +0x24 */ 
    /* +0x28 */ 
    /* +0x2C */ 
    /* +0x30 */ 
    /* +0x34 */ 
    /* +0x38 */ 
    /* +0x3C */ 
    /* +0x40 */ 
    /* +0x44 */ 
    /* +0x48 */ 
    /* +0x4C */ 
    /* +0x50 */ 
    /* +0x54 */ 
    /* +0x58 */ 
    /* +0x5C */ 
    /* +0x60 */ 
    /* +0x64 */ 
    /* +0x68 */ 
    /* +0x6C */ 
    /* +0x70 */ void * slot70(s16 id) { return VCM(void *, (void *, s16), 0x70, id); }
};

struct H { u8 pad000[0x14]; V *obj; };
struct Q { u8 pad000[0x34]; H *h; };
struct E { u8 pad000[0x2C]; s16 id; u8 pad02E[0x2]; void *p; };

extern "C" void IterInit_370170(It *, A *, int, int);
extern "C" E *IterNext_370040(It *);

extern "C" s32 WorldSubsysLinkIds_416a70(D *d, Q *q, int rgp_a2, int rgp_a3)
{
    It it __attribute__((aligned(16)));
    E *e;

    if (q == 0) {
        return 0;
    }
    IterInit_370170(&it, d, (int)rgp_a2, (int)rgp_a3);
    while ((e = IterNext_370040(&it)) != 0) {
    e->p = q->h->obj->slot70(e->id);
    }
    return 1;
}
