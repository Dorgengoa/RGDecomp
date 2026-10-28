/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0

struct O18 {
    u8 pad0[0x12];
    s16 m12;
    u8 pad14[0x13];
    s8 m27;
};

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f150(s32 a0) { VCM(void, (void *, s32), 0x150, a0); }
    
    
    
    
    
    
    
    
    
    void f178(s32 a0) { VCM(void, (void *, s32), 0x178, a0); }
    
    
    void f184(s32 a0) { VCM(void, (void *, s32), 0x184, a0); }
    
    
    void f190(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x190, a0, a1); }
    
    
    
    
    s32 f1A4() { return VCM0(s32, 0x1A4); }
    
    s32 f1AC() { return VCM0(s32, 0x1AC); }
    void f1B0(s32 a0) { VCM(void, (void *, s32), 0x1B0, a0); }
    u8 pad4[0xC];
    s16 *m10;
    u8 pad14[4];
    struct O18 *m18;
};

struct Rec {
    u8 id;
    u8 pad1[3];
    s8 b4;
    s8 b5;
    s8 b6;
    s8 b7[6];
    u8 padD;
};

struct Tbl {
    s16 m0;
    s16 n;
    Rec *recs;
};

extern "C" {
Tbl * WorldSubsysFindRowByKey_3f64e0(s32, long long);
extern s32 D_00465D78[4];
extern u8 *D_004838EC;
}

extern "C" s32 InsectItemSetExp_3d1660(Obj *o, s16 arg1)
{
    s16 *p;
    s32 lim;
    s32 n;
    Tbl *t;
    Rec *r;
    s32 i;
    s32 k;

    o->m18->m12 = arg1;
    p = &o->m18->m12;
    if (*p < 0) {
        *p = 0;
    }
    lim = D_00465D78[0];
    for (;;) {
        n = o->f1AC();
        if (n == 0) {
            o->m18->m12 = 0;
            break;
        }
        if (o->m18->m12 < n) {
            break;
        }
        if (lim <= o->f1A4()) {
            o->m18->m12 = n;
            break;
        }
        o->m18->m12 -= (s16)n;
        o->f1B0(o->m18->m27 + 1);
        t = WorldSubsysFindRowByKey_3f64e0(*(s32 *)(D_004838EC + 0x9C), (long long)(*o->m10));
        r = t->recs;
        for (i = 0; i < t->n; i++, r++) {
            if (r->id == o->m18->m27) {
                o->f150(r->b4);
                o->f178(r->b5);
                o->f184(r->b6);
                for (k = 0; k < 6; k++) {
                    o->f190(k, r->b7[k]);
                }
                break;
            }
        }
    }
    return (s16)(o->m18->m12);
}
