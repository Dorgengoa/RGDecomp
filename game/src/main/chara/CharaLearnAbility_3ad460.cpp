/* rgp:protos */
#line 1
#pragma opt_lifetimes off
#pragma opt_propagation off
#pragma opt_loop_invariants off
#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)

class Ent;

class Slot {
public:
    VC_VPTR_MEMBER;    
    void Init() { VCM0(void, 0x1C); }
                         
    void Activate(void * a0, s32 a1) { VCM(void, (void *, void *, s32), 0x78, a0, a1); }
    Ent *m4;
    u8 pad[0x20];
};

class Ent {
public:
    s16 m0;
    u8 m2;
    u8 m3;
    u8 m4;
    u8 m5;
};

class Info {
public:
    s16 m0;
    u8 m2;
    u8 m3;
    Ent *m4;
};

class Mgr {
public:
    VC_VPTR_MEMBER;                         
    u8 * Find(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(u8 *, (void *, s16, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

class Unit {
public:
    VC_VPTR_MEMBER;           
    void Update() { VCM0(void, 0x38); }
};

typedef struct {
    u64 *b;
    u32 pos;
} BitRef;

extern "C" {
extern void Abort_12de80(void);
extern void Fprintf_12f9a0(s32, u8 *);
extern Info *IterNext_370040(void *);
extern void IterInit_370170(void *, u8 *, int, int);
extern s32 EquipSlotGetAbilityLevel_3a0700(Slot *);
extern s32 EquipSlotGetAbilityIndex_3a0710(Slot *);
extern s32 EquipSlotGetAbilityCompositeId_3a0730(s32);
extern s32 EquipSlotGetRecId_3a0760(Slot *);
extern s32 CharaFindSlotByCompositeId_3ad300(u8 *, s32);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern Info *AbilityListFindByDefId_3f5720(u8 *, s32);
extern s32 AbilityDataGetCompositeId_3f5e10(Ent *);
extern void memcpy(void *, void *, u32);
extern u8 *D_00449858[4];
extern u8 D_00465EA0[];
extern u8 D_00465ED0[];
extern u8 D_004720E0[];
extern u8 D_00472170[];
extern u8 *D_00483818;
extern u8 *D_0048381C;
}

static inline bool bs_test(u64 *bits, u32 pos) {
    volatile BitRef r __attribute__((aligned(16)));
    r.b = bits;
    r.pos = pos;
    if (pos >= 64) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00465ED0);
        Abort_12de80();
    }
    return (*r.b & ((u64)1 << pos)) != 0;
}

static inline void bs_set(u64 *bits, u32 pos) {
    BitRef r __attribute__((aligned(16)));
    r.b = bits;
    r.pos = pos;
    if (((BitRef *)&r)->pos >= 64) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00465EA0);
        Abort_12de80();
    }
    { u64 m_ = 1; *r.b |= m_ << pos; }
}

static inline void bs_reset(u64 *bits, u32 pos) {
    volatile BitRef r __attribute__((aligned(16)));
    r.b = bits;
    r.pos = pos;
    if (pos >= 64) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00465EA0);
        Abort_12de80();
    }
    *r.b &= ~((u64)1 << pos);
}

extern "C" bool CharaLearnAbility_3ad460(u8 *arg0, s32 arg1, int rgp_a2, int rgp_a3) {
    u8 iter[8];
    u32 tmp[10] __attribute__((aligned(16)));
    bool swapped;
    Slot *a;
    u8 k4;
    s32 x0;
    s32 y0;
    Info *e;
    bool found;
    u8 k5;
    bool empty;
    s32 y4;
    s32 kind;
    Ent *ea;
    Ent *eb;
    u32 pos;
    Ent *ent;
    Info *info;
    bool changed;
    s32 old;
    Slot *b;
    u8 *list;
    bool need;
    s32 i;
    s32 x4;


    if (D_0048381C == 0 || *(s16 **)(arg0 + 0x230) == 0) {
        return 0;
    }
    list = (*(Mgr **)(*(u8 **)(D_0048381C + 0x44) + 0xC))->Find(**(s16 **)(arg0 + 0x230), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (list == 0) {
        return 0;
    }
    changed = false;
    old = -1;
    if (*(s32 *)(arg0 + 0x498) != 0) {
        old = EquipSlotGetAbilityCompositeId_3a0730(*(s32 *)(arg0 + 0x498));
    }
    info = AbilityListFindByDefId_3f5720(list, arg1);
    ent = 0;
    if (info != 0) {
        ent = info->m4;
    }
    if (ent == 0) {
        return 0;
    }
    i = info->m0 - 1;
    if (!bs_test((u64 *)(arg0 + 0x2E0), i)) {
        bs_set((u64 *)(arg0 + 0x2E0), i);
        changed = true;
    }
    if (list != 0) {
        list += 4;
    }
    IterInit_370170(iter, list, 0, 0);
    while ((e = IterNext_370040(iter)) != 0) {
        if (e != info && e->m4 != 0 && e->m4->m4 == ent->m4) {
            bs_reset((u64 *)(arg0 + 0x2E0), e->m0 - 1);
        }
    }
    kind = AbilityDataGetCompositeId_3f5e10(ent);
    if (kind == 0x86 && StateFlagTest_3ccd70(*(s32 *)(D_00483818 + 0x10), 0x3ED) == 0) {
        StateFlagSet_3ccb70(*(s32 *)(D_00483818 + 0x10), 0x3ED, 1, 0);
        StateFlagSet_3ccb70(*(s32 *)(D_00483818 + 0x10), 0x3EE, 1, 0);
    }
    if (ent->m2 == 0 || kind == 0x86) {
        a = (Slot *)(arg0 + 0x308);
        found = false;
        for (i = 0; i < 10; i++, a++) {
            if (a->m4 != 0 && EquipSlotGetRecId_3a0760(a) > 0) {
                k4 = ent->m4;
                if (k4 == ((unsigned char)EquipSlotGetAbilityIndex_3a0710(a))) {
                    k5 = ent->m5;
                    if (k5 == ((unsigned char)EquipSlotGetAbilityLevel_3a0700(a))) {
                        found = true;
                        break;
                    }
                    a->Activate(arg0, arg1);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            a = (Slot *)(arg0 + 0x308);
            for (x0 = 0; x0 < 10; x0++, a++) {
                empty = true;
                if (a->m4 != 0 && EquipSlotGetRecId_3a0760(a) > 0) {
                    empty = false;
                }
                if (empty) {
                    a->Activate(arg0, arg1);
                    break;
                }
            }
        }
    }
    do {
        swapped = false;
        a = (Slot *)(arg0 + 0x308);
        b = (Slot *)(arg0 + 0x330);
        i = 1;
        do {
            ea = a->m4;
            eb = b->m4;
            need = false;
            if (ea == 0 && eb != 0) {
                need = true;
            } else if (ea != 0 && eb != 0) {
                x0 = ea->m0;
                y0 = eb->m0;
                x4 = ea->m4;
                y4 = eb->m4;
                if (x4 > y4 || (x0 > 0 && y0 <= 0)) {
                    need = true;
                }
            }
            if (need) {
                tmp[0] = (u32)D_00472170;
                ((Slot *)tmp)->Init();
                tmp[0] = (u32)D_004720E0;
                ((Slot *)tmp)->Init();
                memcpy(tmp, b, 0x28);
                memcpy(b, a, 0x28);
                memcpy(a, tmp, 0x28);
                swapped = true;
            }
            a = b;
            b++;
            i++;
        } while (i < 10);
    } while (swapped);
    if (old >= 0) {
        *(s32 *)(arg0 + 0x498) = CharaFindSlotByCompositeId_3ad300(arg0, old);
    }
    ((Unit *)arg0)->Update();
    return changed;
}
