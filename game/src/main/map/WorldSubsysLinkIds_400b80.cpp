/* rgp:protos */
#line 1
#include "types.h"

class V {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f70(s32 a0) { return VCM(s32, (void *, s32), 0x70, a0); }
};

typedef struct {
    u8 pad0[8];
    V *unk8;
    u8 padC[4];
    V *unk10;
} Holder;

typedef struct {
    u8 pad0[0x60];
    Holder *unk60;
} Obj;

typedef struct {
    u8 pad0[8];
    s32 unk8[2];
} E1;

typedef struct {
    s16 unk0;
    u8 pad2[0x2E - 2];
    s16 unk2E;
    s32 unk30;
} E2;

typedef struct {
    __extension__ signed short b : 10;
} __attribute__((aligned(2))) R;

typedef struct {
    s32 a;
    s32 b;
} Iter;

extern "C" {
void *IterNext_370040(Iter *);
void IterReset_3700f0(Iter *);
void IterInit_370170(Iter *, void *, int, int);
R * TableFindMaxKey_401580(s32, int, int, int);
}

static inline void *NextA(Iter *p) { return IterNext_370040(p); }
extern "C" s32 WorldSubsysLinkIds_400b80(u8 *arg0, Obj *arg1, int rgp_a2, int rgp_a3)
{
    Iter it __attribute__((aligned(16)));
    void *e;
    s32 i;
    s32 *p;
    s32 r;
    R *q;
    u8 *t;

    if (arg1 == NULL) {
        return 0;
    }
    t = arg0;
    if (t != NULL) {
        t += 0x88;
    }
    IterInit_370170(&it, t, (int)rgp_a2, (int)rgp_a3);
    while ((e = NextA(&it)) != NULL) {
        for (i = 0; i < 2; i++) {
            p = &((E1 *)e)->unk8[i];
            *p = arg1->unk60->unk8->f70(*(s16 *)p);
        }
    }
    IterReset_3700f0(&it);
    while ((e = IterNext_370040(&it)) != NULL) {
        r = arg1->unk60->unk10->f70(((E2 *)e)->unk0);
        ((E2 *)e)->unk30 = r;
        if (r != 0 && (q = TableFindMaxKey_401580(r, 0, 0, 0)) != NULL) {
            ((E2 *)e)->unk2E = q->b;
        } else {
            ((E2 *)e)->unk2E = 0;
        }
    }
    return 1;
}
