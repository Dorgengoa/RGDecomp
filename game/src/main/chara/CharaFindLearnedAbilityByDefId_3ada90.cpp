/* rgp:protos */
#line 1
#include "types.h"

class VObj {
public:
    VC_VPTR_MEMBER;   
       
       
       
       
       
     
    s32 Find(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

struct Holder {
    u8 pad0[0xC];
    VObj *obj;
};

struct Glob {
    u8 pad0[0x44];
    Holder *holder;
};

struct Ent {
    s16 unk0;
    s32 unk4;
};

struct Err {
    u8 pad0[0xC];
    s32 unkC;
};

extern "C" {
void Abort_12de80();
void Fprintf_12f9a0(s32, void *);
Ent *AbilityListFindByDefId_3f5720(s32, s32);
}
extern "C" Err *D_00449858[];
extern "C" u8 D_00465ED0[];
extern "C" Glob *D_0048381C;

class BitRef {
public:
    u64 *p;
    u32 i;
    BitRef(u64 *p_, u32 i_) : p(p_), i(i_) {}
};
static inline bool BitTest3(u64 *p, u32 i) {
    BitRef r(p, i);
    BitRef *q = &r;
    if (q->i >= 64) {
        Fprintf_12f9a0(D_00449858[0]->unkC, D_00465ED0);
            Abort_12de80();
    }
    return (*q->p & ((u64)1 << i)) != 0;
}
struct Self {
    u8 pad0[0x230];
    s16 *unk230;
    u8 pad1[0x2E0 - 0x234];
    u64 bits[1];
};

extern "C" s32 CharaFindLearnedAbilityByDefId_3ada90(Self *arg0, s32 arg1, s32 arg2, int rgp_a3) {
    Glob *g;
    s32 r;
    Ent *e;
    s32 ret;


    g = D_0048381C;
    if (g == 0 || arg0->unk230 == 0) {
        return 0;
    }
    r = g->holder->obj->Find(*arg0->unk230, (int)(long)(arg2), (int)(long)(rgp_a3));
    if (r == 0) {
        return 0;
    }
    ret = 0;
    arg2 = (u8)arg2;
    e = AbilityListFindByDefId_3f5720(r, arg1);
    if (e != 0) {
        if (BitTest3(&arg0->bits[arg2], e->unk0 - 1)) {
            ret = e->unk4;
        }
    }
    return ret;
}
