/* rgp:protos */
#line 1
#include "types.h"

#pragma divbyzerocheck on

class VT3ca890 {
public:
    VC_VPTR_MEMBER;    
        
        
        
        
    
    s16 * find(s16 id, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s16 *, (void *, s16, int, int), 0x70, id, rgp_fwd2, rgp_fwd3); }
};

typedef struct {
    u8 pad0[0x8];
    VT3ca890 *m8;
    VT3ca890 *mC;
} Tbl3ca890;

typedef struct {
    u8 pad0[0x34];
    Tbl3ca890 *m34;
} Mgr3ca890;

typedef struct {
    u8 pad0[0x2C];
    s16 m2C;
} Ent3ca890;

typedef struct {
    s32 m0;
    s16 *m4;
    s16 *m8;
} Node3ca890;

typedef struct {
    u32 w[2];
} Iter3ca890;

typedef struct {
    u8 pad0[0x4];
    s16 m4;
    s16 m6;
    s16 m8;
    u8 padA[0x14 - 0xA];
    s16 *m14;
    Ent3ca890 *m18;
    s16 *m1C;
    u8 pad20[0x118 - 0x20];
    s64 m118;
    s32 m120;
    s32 m124;
    f32 m128;
    f32 m12C;
    f32 m130;
    f32 m134;
    f32 m138;
    s16 m13C;
    u8 pad13E[2];
    s32 m140;
    u8 pad144[0xC];
    s32 m150;
    s32 m154;
    s32 m158;
    s32 m15C;
} Obj3ca890;

extern "C" {
Node3ca890 *IterNext_370040(Iter3ca890 *);
void IterReset_3700f0(Iter3ca890 *);
void IterInit_370170(Iter3ca890 *, void *, int, int);
void PartySetAreaMaybe_3cab50(Obj3ca890 *, s16, s32, s32);
void HandleEntriesReleaseAll_3ec300(void *);
void *WorldSubsysGetPlanetAreaView_411290(Tbl3ca890 *, s32);
extern f32 D_00465940[];
extern void *D_00483890;
extern Mgr3ca890 *D_00483894;
}

static inline void reset3ca890(Obj3ca890 *o)
{
    o->m118 = 0;
    o->m120 = 0;
    o->m124 = 0;
    o->m128 = D_00465940[0];
    o->m12C = D_00465940[0];
    o->m130 = D_00465940[0];
    o->m134 = D_00465940[0];
    o->m138 = 11.0f;
    o->m13C = 0;
    o->m140 = 0;
    o->m150 = 0;
    o->m154 = 0;
    o->m158 = 0;
    o->m15C = 0;
}

static inline bool ieq(s32 a, s32 b) { return a == b; }
extern "C" s32 PartySetSubAreaMaybe_3ca890(Obj3ca890 *arg0, s32 arg1, s32 arg2, int rgp_a3)
{
    Iter3ca890 it __attribute__((aligned(16)));
    s16 *v;
    s16 old;
    s32 id;
    s32 k;
    bool same;
    Node3ca890 *n;
    s16 *r;

    if (D_00483894 == NULL) {
        return 0;
    }
    if (D_00483890 == NULL) {
        return 0;
    }
    v = D_00483894->m34->m8->find(arg1, (int)(long)(arg2), (int)(long)(rgp_a3));
    if (v == NULL) {
        return 0;
    }
    old = arg0->m6;
    arg0->m6 = *v;
    arg0->m18 = (Ent3ca890 *)v;
    if (arg2 != 0) {
        k = arg0->m18->m2C;
        if (k >= 0) {
            same = false;
            if (arg0->m14 != NULL && arg0->m4 == *arg0->m14 && arg0->m4 == k) {
                same = true;
            }
            if (!same) {
                PartySetAreaMaybe_3cab50(arg0, k, 0, 0);
            }
            IterInit_370170(&it, WorldSubsysGetPlanetAreaView_411290(D_00483894->m34, -1), 0, 0);
            id = -1;
            IterReset_3700f0(&it);
            while ((n = IterNext_370040(&it)) != NULL) {
                if (n->m4 != NULL && n->m8 != NULL && arg0->m6 == *n->m4) {
                    id = *n->m8;
                    break;
                }
            }
            if (id < 0) {
                IterReset_3700f0(&it);
                while ((n = IterNext_370040(&it)) != NULL) {
                    if (ieq(arg0->m4, *(volatile s32 *)&n->m0 / 10000000 % 100)) {
                        if (n->m8 != NULL) {
                            id = *n->m8;
                        } else {
                            id = -1;
                        }
                        break;
                    }
                }
            }
            if (id >= 0 && D_00483894 != NULL) {
                r = D_00483894->m34->mC->find(id);
                if (r != NULL && arg0->m8 != id) {
                    arg0->m8 = id;
                    arg0->m1C = r;
                    reset3ca890(arg0);
                }
            }
        }
    }
    HandleEntriesReleaseAll_3ec300(D_00483890);
    reset3ca890(arg0);
    return 1;
}
