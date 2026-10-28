/* rgp:protos */
#line 1
#include "types.h"

typedef struct Item {
    u8 pad0[0x2];
    s8 x2;
    u8 pad3[0x1];
    s8 x4;
    u8 pad5[0x35];
    s16 x3A;
    s16 x3C;
    s16 x3E;
    s16 x40;
    u8 pad42[0x2];
    s16 *x44;
    s16 x48;
    u8 pad4A[0x2];
    s16 *x4C;
    s16 x50;
    u8 pad52[0x2];
    s16 *x54;
} Item;

class DB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * Get(s16 a0) { return VCM(Item *, (void *, s16), 0x70, a0); }
};

typedef struct Mgr2 {
    u8 pad0[0x8];
    DB *x8;
} Mgr2;

typedef struct Mgr {
    u8 pad0[0x58];
    Mgr2 *x58;
} Mgr;

typedef struct Mgr3 {
    u8 pad0[0x20];
    s32 x20;
} Mgr3;

typedef struct Dbg {
    u8 pad0[0xC];
    s32 xC;
} Dbg;

typedef struct Tmp {
    u8 d[0x28];
} Tmp;

class Chr;

extern "C" {
extern void Abort_12de80(void);
extern void Fprintf_12f9a0(s32, char *);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetStatusEffect_2d9010(void);
extern void PartyAllySuggestCancel_2eea00(s32);
extern void StatusEffectStopMatching_33c1c0(s32, s32, s32);
extern void StatusEffectStart_33c240(s32, s32, s32, s32);
extern void CharaSysEventLogRecordOpenHud_3a3260(s32, s32, s32, s32, s32);
extern s32 CharaIsNonLeaderMember_3ae140(s32);
extern s32 ActorCastToChara_3b87b0(Chr *, int, int, int);
extern void CharaUsePartySkillMaybe_3e08b0(s32, s32);
extern void EventFireTriggers_3e2660(Tmp *, s32);
extern void ActionPacketInitMonographStatusMaybe_3e2ff0(Tmp *, s32, Chr *);
extern void ActionPacketReset_3e3d00(Tmp *);
extern Dbg *D_00449858 __attribute__((section(".data")));
extern char D_0045CB40[];
extern char D_00466000[];
extern f32 D_0047D278;
extern Mgr3 *D_00483818;
extern Mgr *D_0048381C;
}

class BitRef {
public:
    u64 *p;
    u32 i;
    BitRef(u64 *b, u32 n) {
        p = b;
        i = n;
    }
    bool Get() {
        u32 n = i;
        if (n >= 0x30) {
            Fprintf_12f9a0(D_00449858->xC, D_0045CB40);
            Abort_12de80();
        }
        return (*p & ((u64)1 << n)) != 0;
    }
    void Put(s32 v) {
        u32 n = i;
        if (n >= 0x30) {
            Fprintf_12f9a0(D_00449858->xC, D_00466000);
            Abort_12de80();
        }
        u64 m = (u64)1 << n;
        if (v != 0) {
            *p |= m;
        } else {
            *p &= ~m;
        }
    }
};

#define Test(b, n) BitRef(b, n).Get()
#define Assign(b, n, v) BitRef(b, n).Put(v)

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void Refresh() { VCM0(void, 0x38); }
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Check(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Enable(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A0, a0, a1, a2); }

    u8 pad4[0x8];
    s32 xC;
    u8 pad10[0xB8];
    u64 xC8;
    f32 xD0[0x20];
    s16 x150[0x10];
};

extern "C" s32 CharaStatusSetMaybe_3b73c0(Chr *c, s32 idx, s32 on) {
    Tmp tmp __attribute__((aligned(16)));
    s32 q;
    Item *it;
    DB *db;
    s32 a;
    s32 b;
    s32 k;
    bool chg;
    s32 n;
    s16 *l;
  s16 *l_w100;
    s16 *l2;
    s32 i;
    s32 t;
    f32 f;
    u8 ok;
    Item *it2;
    s32 j;
    s32 r;
    s32 g;

    if (D_0048381C == 0) {
        return 0;
    }
    q = GetStatusEffect_2d9010();
    db = D_0048381C->x58->x8;
    if (db != 0) {
        it = db->Get(idx);
    } else {
        it = 0;
    }
    if (it == 0) {
        return 0;
    }
    if (idx == 10) {
        idx = 5;
    }
    a = it->x3A;
    b = it->x3C;
    k = it->x4;
    chg = false;
    if (on == 0) {
        if (!Test(&c->xC8, idx)) {
            return 0;
        }
        Assign(&c->xC8, idx, 0);
        if (a > 0 && b >= 0 && c->x150[b] == idx) {
            c->xD0[b] = 0.0f;
            c->x150[b] = -1;
        }
        if (q != 0 && k >= 0) {
            StatusEffectStopMatching_33c1c0(q, k, c->xC);
            chg = true;
        }
        n = it->x50;
        l = it->x54;
        if (n > 0 && l != 0) {
            for (i = 0; i < n; i++, l++) {
                c->Enable(*l, 1, 1);
            }
        }
        if (chg) {
            c->Refresh();
        }
        if (idx == 0x1F) {
            CharaSysEventLogRecordOpenHud_3a3260(D_00483818->x20, 0x3E7, c->xC, 0x46, 1);
            g = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(&tmp);
            ActionPacketInitMonographStatusMaybe_3e2ff0(&tmp, g, c);
            EventFireTriggers_3e2660(&tmp, 0);
        }
        return 1;
    }
    if (on != 0 && Test(&c->xC8, idx)) {
        if (a <= 0 || b < 0) {
            return 0;
        }
        t = it->x3E;
        if (t == 0) {
            return 0;
        }
        if (c->x150[b] == idx) {
            f = a;
            ok = 0;
            if (t == 1) {
                ok = 1;
            } else if (t == 2) {
                ok = 1;
                f += c->xD0[b];
            }
            if (ok) {
                c->xD0[b] = f;
                if (q != 0 && k >= 0) {
                    StatusEffectStopMatching_33c1c0(q, k, c->xC);
                    StatusEffectStart_33c240(q, k, c->xC, -1);
                }
                return 1;
            }
        }
    }
    n = it->x48;
    l_w100 = it->x4C;
    if (n > 0 && l_w100 != 0) {
        for (i = 0; i < 0x30; i++) {
            if (Test(&c->xC8, i)) {
                db = D_0048381C->x58->x8;
                if (db != 0) {
                    it2 = db->Get(i);
                } else {
                    it2 = 0;
                }
                if (it2 != 0) {
                    s16 *p = l_w100;
                    s32 j;
                    for (j = 0; j < n; j++, p++) {
                        if (it2->x2 == *p) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    n = it->x40;
    l2 = it->x44;
    if (n > 0 && l2 != 0) {
        for (i = 0; i < 0x30; i++) {
            if (Test(&c->xC8, i)) {
                Item *it3;
                db = D_0048381C->x58->x8;
                if (db != 0) {
                    it3 = db->Get(i);
                    it3 = (Item *)(u32)it3;
                } else {
                    it3 = 0;
                }
                if (it3 != 0) {
                    s16 *p = l2;
                    s32 j;
                    for (j = 0; j < n; j++, p++) {
                        if (it3->x2 == *p) {
                            c->Enable(i, 0, 0);
                        }
                    }
                }
            }
        }
    }
    r = ActorCastToChara_3b87b0(c, 0, 0, 0);
    if (on != 0 && r != 0) {
        if (idx == 4) {
            CharaUsePartySkillMaybe_3e08b0(c->xC, 1);
        } else if (idx == 9) {
            CharaUsePartySkillMaybe_3e08b0(c->xC, 0);
        }
    }
    Assign(&c->xC8, idx, on);
    if (a > 0 && b >= 0) {
        f = a;
        if (idx == 5 && r != 0 && ((unsigned char)CharaIsNonLeaderMember_3ae140(r)) != 0) {
            f *= D_0047D278;
        }
        c->x150[b] = idx;
        c->xD0[b] = f;
    }
    if (q != 0 && k >= 0) {
        StatusEffectStart_33c240(q, k, c->xC, -1);
    }
    c->Refresh();
    if (c->Check(0) == 0 || Test(&c->xC8, 3)) {
        PartyAllySuggestCancel_2eea00(c->xC);
    }
    return 1;
}
