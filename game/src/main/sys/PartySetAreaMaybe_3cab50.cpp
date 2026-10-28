/* rgp:protos */
#line 1
#pragma divbyzerocheck on
#include "types.h"
#pragma opt_dead_assignments off

class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s16 x0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, x0, rgp_fwd2, rgp_fwd3); }
};

struct Tables {
    u8 pad0[0xC];
    VC *xC;
    u8 pad10[4];
    VC *x14;
};

struct Mgr {
    u8 pad0[0x34];
    Tables *x34;
};

struct Cur {
    u8 pad0[4];
    s16 x4;
};

struct Ctx {
    u8 pad0[0x18];
    Cur *x18;
};

struct Rec18 {
    s16 x0;
    u8 pad2[0x2A];
    s16 x2C;
};

struct Node {
    s32 x0;
    s16 *x4;
    s16 *x8;
};

struct Info {
    u8 pad0[8];
    s16 *x8;
};

struct Iter {
    s32 x0;
    s32 x4;
};

struct Self {
    u8 pad0[4];
    s16 x4;
    s16 x6;
    s16 x8;
    u8 padA[0xA];
    s32 x14;
    Rec18 *x18;
    s32 x1C;
    u8 pad20[0x118 - 0x20];
    s64 x118;
    s32 x120;
    s32 x124;
    f32 x128;
    f32 x12C;
    f32 x130;
    f32 x134;
    f32 x138;
    s16 x13C;
    u8 pad13E[2];
    s32 x140;
    u8 pad144[0xC];
    s32 x150;
    s32 x154;
    s32 x158;
    s32 x15C;
    u8 pad160[0x4CA8 - 0x160];
    s16 x4CA8;
};

extern "C" {
Node *IterNext_370040(Iter *);
void IterInit_370170(Iter *, s32, int, int);
void PartySetSubAreaMaybe_3ca890(Self *, s32, s32, int);
void PartyResetZoneListsMaybe_3cb210(Self *, bool);
void WorldOnPartyAreaChanged_3ec350(Ctx *, long long, long long);
bool PlanetEntryIsReadyMaybe_3ec4f0(Ctx *, s32);
void PlanetEntryRequestLoadMaybe_3ec600(Ctx *, s16);
void TranspParamRefreshCondsMaybe_3ecce0(Ctx *, s32);
void BgmParamRefreshCondsMaybe_3ece90(Ctx *, s32);
void MapObjParamRefreshCondsMaybe_3ed0a0(Ctx *, s32);
Info *PlanetAreaMatrixLookupByProgress_3ed840(Ctx *, s16);
void WorldDataMgrReset_3f1c60(Mgr *);
s32 WorldSubsysGetPlanetAreaView_411290(Tables *, s32);
extern f32 D_00465940[];
extern Ctx *D_00483890;
extern Mgr *D_00483894;
}

static inline void reset(Self *self) {
    self->x118 = 0;
    self->x120 = 0;
    self->x124 = 0;
    self->x128 = D_00465940[0];
    self->x12C = D_00465940[0];
    self->x130 = D_00465940[0];
    self->x134 = D_00465940[0];
    self->x138 = 11.0f;
    self->x13C = 0;
    self->x140 = 0;
    self->x150 = 0;
    self->x154 = 0;
    self->x158 = 0;
    self->x15C = 0;
}

extern "C" s32 PartySetAreaMaybe_3cab50(Self *self, s32 arg1, s32 arg2, s32 arg3) {
    Iter it __attribute__((aligned(16)));
    s32 r;
    bool changed;
    s32 old;
    s32 cur;
    bool hit;
    s32 idx;
    s32 sel;
    Node *n;
    s16 *p4;
    s16 *p8;
    s32 k;
    s32 q;
    bool found;
    Info *info;
    s32 r2;
    bool a;
    bool b;
    bool c;

    if (D_00483894 == 0) {
        return 0;
    }
    if (D_00483890 == 0) {
        return 0;
    }
    r = D_00483894->x34->x14->f(arg1, (int)(long)(arg2), (int)(long)(arg3));
    if (r == 0) {
        return 0;
    }
    cur = self->x4;
    changed = false;
    if (cur != arg1) {
        changed = true;
    }
    old = (s16)cur;
    if (changed && old != 9) {
        self->x4CA8 = old;
    }
    self->x4 = arg1;
    self->x14 = r;
    if (D_00483894 != 0 && arg2 != 0) {
        idx = -1;
        sel = -1;
        hit = false;
        if (self->x18 != 0 && self->x18->x0 == self->x6 && self->x18->x2C == self->x4) {
            hit = true;
        }
        if (!hit) {
            IterInit_370170(&it, WorldSubsysGetPlanetAreaView_411290(D_00483894->x34, -1), 0, 0);
            found = false;
            while ((n = IterNext_370040(&it)) != 0) {
                if (n->x4 != 0 && n->x8 != 0) {
                    q = n->x0 / 10000000 % 100;
                    k = *n->x4;
                    if (self->x4 == q) {
                        if (self->x6 == k) {
                            sel = *n->x8;
                            found = true;
                            break;
                        }
                        if (idx < 0) {
                            sel = *n->x8;
                            idx = k;
                        }
                    }
                }
            }
            if (found) {
                idx = -1;
            }
        }
        if (D_00483890 != 0) {
            info = PlanetAreaMatrixLookupByProgress_3ed840(D_00483890, D_00483890->x18->x4);
            if (info != 0 && info->x8 != 0) {
                sel = *info->x8;
            }
        }
        if (idx >= 0) {
            PartySetSubAreaMaybe_3ca890(self, idx, 0, 0);
        }
        if (sel >= 0 && D_00483894 != 0) {
            r2 = D_00483894->x34->xC->f(sel);
            if (r2 != 0 && self->x8 != sel) {
                self->x8 = sel;
                self->x1C = r2;
                reset(self);
            }
        }
    }
    a = PlanetEntryIsReadyMaybe_3ec4f0(D_00483890, 1);
    b = PlanetEntryIsReadyMaybe_3ec4f0(D_00483890, self->x4);
    c = false;
    if (!b) {
        c = true;
    }
    PartyResetZoneListsMaybe_3cb210(self, c);
    if (c && D_00483894 != 0) {
        WorldDataMgrReset_3f1c60(D_00483894);
    }
    if (!a) {
        PlanetEntryRequestLoadMaybe_3ec600(D_00483890, 1);
    }
    if (!b && self->x4 != 1) {
        PlanetEntryRequestLoadMaybe_3ec600(D_00483890, self->x4);
    }
    if (changed && arg3 == 0) {
        WorldOnPartyAreaChanged_3ec350(D_00483890, (long long)(self->x4), (long long)(old));
    }
    reset(self);
    if (changed && a) {
        if (arg3 == 0) {
            MapObjParamRefreshCondsMaybe_3ed0a0(D_00483890, 1);
        }
        if (arg3 == 0) {
            BgmParamRefreshCondsMaybe_3ece90(D_00483890, 1);
        }
        if (arg3 == 0) {
            TranspParamRefreshCondsMaybe_3ecce0(D_00483890, 1);
        }
    }
    return 1;
}
