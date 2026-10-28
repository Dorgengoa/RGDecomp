/* rgp:protos */
#line 1
#include "types.h"

typedef struct Kind { s8 pad[2]; s8 type; } Kind;
typedef struct Ent { u8 pad[0x10]; Kind *kind; } Ent;
typedef struct Mgr { u8 pad[0x18]; s32 f18; } Mgr;
typedef struct Iter { s32 a; s32 b; } Iter;
typedef struct Query { s32 v[8]; } Query;
typedef struct Obj { u8 pad[0x5C]; s8 f5C; s8 f5D; u8 pad2[0xFC - 0x5E]; s16 count; s16 padFE; Ent *list[240]; } Obj;
class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * v388() { return VCM0(Ent *, 0x388); }
    Ent * v38C() { return VCM0(Ent *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * v3C4() { return VCM0(Ent *, 0x3C4); }
    
    
    
    
    Ent * v3D8() { return VCM0(Ent *, 0x3D8); }
};

extern "C" {
extern Mgr *GetGameData_1fede0(void);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern Chr *PartyGetSlotChara_3c2fb0(s32, s32);
extern void InvViewCtorFromOwner_3cec70(Query *, Mgr *, s32, s32, s32, s32);
extern void IterInit_370170(Iter *, Query *, int, int);
extern Ent *IterNext_370040(Iter *);
extern Chr *PartyFindItemHolder_3d4c20(Ent *);
extern s32 ItemIsEquippableBy_3d4750(Ent *, Chr *, s32, s32);
extern s32 D_00450980[5];
}

extern "C" s32 MenuEquipCandidatesFill_29e290(Obj *arg0, s32 arg1) {
    s32 tbl[5] __attribute__((aligned(16)));
    Query q __attribute__((aligned(16)));
    Iter it __attribute__((aligned(16)));
    Chr *chr;
    s32 n;
    Ent *sel;
    Ent *e;
    Mgr *mgr;
    s32 idx;
    s32 i;
    Chr *owner;
    s32 *s;
    s32 *p;
    s32 k;
    s32 ty;
    Kind *kd;
    s32 *tp;

    mgr = GetGameData_1fede0();
    k = PartyCountMembers_3c2010(mgr->f18, 1, 1);
    idx = arg0->f5C + arg0->f5D * k;
    if (idx < 0 || idx > 10) return 0;
    for (i = 0; i < 240; i++) {
        arg0->list[i] = 0;
    }
    if (arg1 > 3) return 0;
    s = D_00450980;
    p = tbl;
    k = 5;
    do {
        *p++ = *s++;
    } while (--k > 0);
    chr = PartyGetSlotChara_3c2fb0(mgr->f18, idx);
    if (chr == 0) return 0;
    InvViewCtorFromOwner_3cec70(&q, mgr, 0, -1, -1, -1);
    IterInit_370170(&it, &q, 0, 0);
    n = 0;
    while (e = IterNext_370040(&it), e != 0) {
        ty = tbl[arg1];
        if (ty != e->kind->type) continue;
        owner = PartyFindItemHolder_3d4c20(e);
        if (owner != 0 && owner == chr) {
            if (arg1 == 0) sel = chr->v388();
            else if (arg1 == 1) sel = chr->v38C();
            else if (arg1 == 2) sel = chr->v3C4();
            else if (arg1 == 3) sel = chr->v3D8();
            if (e != sel) {
                arg0->list[0] = e;
            }
        } else if (((unsigned char)ItemIsEquippableBy_3d4750(e, chr, tbl[arg1], 1)) != 0) {
            arg0->list[n++] = e;
        }
    }
    arg0->count = n;
    return 1;
}
