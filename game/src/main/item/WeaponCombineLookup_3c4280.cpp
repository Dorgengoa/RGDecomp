#include "types.h"

struct Hdr { s16 m0; s8 m2; u8 pad3[5]; s16 m8; };
struct Rec { u8 m0; u8 m1; u8 m2; };
struct Ent { u8 m0; u8 pad1[2]; u8 k : 4; u8 f : 1; u8 r : 3; s16 m4; };
struct Obj { u8 pad0; u8 m1; u8 pad2[2]; Ent *m4; };
struct Grp;
struct Lnk { u8 pad0; u8 m1; };

struct VA {
    VC_VPTR_MEMBER;   
       
       
       
       
       
     
    void * get(s16 id) { return VCM(void *, (void *, s16), 0x70, id); }
    u8 pad[0x90];
    u8 m94;
};
struct VB {
    VC_VPTR_MEMBER;   
       
       
       
       
       
     
    s32 get(s16 id) { return VCM(s32, (void *, s16), 0x70, id); }
};
struct S90 { u8 pad[0xC]; VA *mC; };
struct S40 { u8 pad[0x8]; VB *m8; };
struct Glob { u8 pad[0x40]; S40 *m40; u8 pad44[0x4C]; S90 *m90; };
extern "C" Glob *D_00483894;

extern "C" {
Obj *ListFindByKey_407ee0(void *, s32);
Rec *RecTableBinSearch_407bb0(Obj *, s32, s32);
Grp *ListBinSearchByKey_407b40(Obj *, s32);
Lnk *ListBinSearchByKey_4079d0(Grp *, s32);
Ent *RecTableFindByByteId_407c70(Obj *, s32);
}

extern "C" s32 WeaponCombineLookup_3c4280(s32 pd0, Hdr *a, s32 arg2, Hdr *b, s32 arg4, s32 *outDiff, u8 *outFlag, u8 *outBit,
                            s32 *outOff, Rec **outA, Rec **outB, Ent **outE)
{
    Obj *o;
    Rec *ra;
    Rec *rb;
    s32 x;
    s32 y;
    s32 mn;
    s32 c;
    s32 d;
    Grp *ga;
    Grp *gb;
    Lnk *e;
    s32 cur;
    Ent *found;
    Ent *p;
    s32 i;
    s32 k;
    s32 lim;
    s32 r;
    s8 ka;
    s32 ia;
    s32 ib;
    void *v;
    s32 ret;
    s32 id;
    s32 n;
    s32 u;
    s32 kk;

    if (a == 0 || b == 0) {
        return 0;
    }
    *outDiff = 0;
    *outFlag = 0;
    *outBit = 0;
    *outOff = 0;
    if (outA != 0) {
        *outA = 0;
    }
    if (outB != 0) {
        *outB = 0;
    }
    if (outE != 0) {
        *outE = 0;
    }
    id = a->m8;
    if (id != b->m8) {
        goto fail;
    }
    ka = a->m2;
    if (ka == b->m2) {
        goto body;
    }
fail:
    return 0;
body:
    ia = a->m0;
    ib = b->m0;
    v = D_00483894->m90->mC->get(id);
    if (v == 0) {
        return 0;
    }
    o = ListFindByKey_407ee0(v, ka);
    if (o == 0) {
        return 0;
    }
    ra = RecTableBinSearch_407bb0(o, ia, arg2);
    rb = RecTableBinSearch_407bb0(o, ib, arg4);
    if (ra == 0 || rb == 0) {
        return 0;
    }
    x = ra->m0;
    y = rb->m0;
    *outDiff = x - y;
    if (x >= y) {
        mn = x;
    } else {
        mn = y;
    }
    c = ra->m1;
    d = rb->m1;
    ga = ListBinSearchByKey_407b40(o, c);
    gb = ListBinSearchByKey_407b40(o, d);
    if (ga == 0 || gb == 0) {
        return 0;
    }
    e = ListBinSearchByKey_4079d0(ga, d);
    if (e == 0) {
        e = ListBinSearchByKey_4079d0(gb, c);
    }
    if (e == 0) {
        return 0;
    }
    if (ra->m2 == y || rb->m2 == x) {
        *outFlag = 1;
    }
    cur = e->m1;
    found = RecTableFindByByteId_407c70(o, cur);
    if (found == 0) {
        return 0;
    }
    if (*outFlag != 0) {
        lim = cur + D_00483894->m90->mC->m94;
        k = found->k;
        n = o->m1;
        p = o->m4;
        for (i = 0; i < n; i++, p++) {
            u = p->m0;
            kk = p->k;
            if (cur < u && u <= lim && kk == k) {
                found = p;
                cur = u;
                if (u == lim) {
                    break;
                }
            }
        }
    }
    r = D_00483894->m40->m8->get(found->m4);
    *outBit = found->f != 0;
    *outOff = found->m0 - (s32)mn;
    if (outA != 0) {
        *outA = ra;
    }
    if (outB != 0) {
        *outB = rb;
    }
    if (outE != 0) {
        *outE = found;
    }
    return r;
}
