/* rgp:protos */
#line 1
#include "types.h"

typedef struct Ent3a3 {
    s16 a;
    s16 b;
    void *obj;
} Ent3a3;

typedef struct Slot3a3 {
    struct Unit3a3 *p;
    s16 c;
    s16 pad;
} Slot3a3;

typedef struct Grp3a3 {
    s16 avg;
    s16 n;
    Slot3a3 e[5];
} Grp3a3;

typedef struct Rw3a3 {
    s16 id;
    s16 v;
} Rw3a3;

typedef struct Item3a3 {
    __extension__ unsigned short id:5;
    unsigned short pct:8;
    unsigned short p0:3;
    unsigned char lo:4;
    unsigned char hi:4;
    unsigned char  : 0, p1:8;
} __attribute__((aligned(4))) Item3a3;

typedef struct Src10 {
    u8 pad0[0x2D];
    s8 n;
    u8 pad2E[6];
    Item3a3 *list;
} Src10;

typedef struct Bits7C {
    __extension__ signed short a:5;
    signed short n:5;
    signed short b:6;
} __attribute__((aligned(2))) Bits7C;

typedef struct Vec3a3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3a3;

typedef struct Src18 {
    u8 pad0[0x10];
    s16 m10;
    u8 pad12[0x44 - 0x12];
    Vec3a3 v;
    u8 pad50[0x7C - 0x50];
    Bits7C bits;
    u8 pad7E[6];
    Item3a3 *list;
} Src18;

typedef struct Desc3a3 {
    u8 pad0[8];
    s16 m8;
    s16 mA;
    s16 mC;
    u8 padE[2];
    Src10 *m10;
    s32 m14;
    Src18 *m18;
    u8 pad1C[8];
    u8 b0:1;
    u8 b1:1;
    u8 b2:1;
    u8 b3:1;
    u8 b4:4;
    u8 pad25[7];
    s16 m2C;
    s16 m2E;
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
    f32 m40;
    s16 m44;
    u8 pad46[2];
    Ent3a3 ent[28];
    Grp3a3 grp;
    s16 m154;
    Rw3a3 rw[3];
    s16 m162;
    s16 m164;
    s16 m166;
    s16 m168;
    u8 pad16A[0x178 - 0x16A];
    u64 m178;
    u64 m180;
    u64 m188;
} Desc3a3;

typedef struct Flags3a3 {
    u8 b0:1;
    u8 b1:7;
} Flags3a3;

class VObj37C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    void u8() { VCM0(void, 0x28); }
    
    
    
    
    
    
    
    void u16() { VCM0(void, 0x48); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void u64() { VCM0(void, 0x108); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f37C(s16 a0) { VCM(void, (void *, s16), 0x37C, a0); }
};

typedef struct Unit3a3 {
    s16 id;
    u8 pad2[0x2C - 2];
    u16 m2C;
    u8 pad2E[0x80 - 0x2E];
    u8 p0:5;
    u8 f5:1;
    u8 f6:1;
    u8 p7:1;
} Unit3a3;

class VObj70 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    void u8() { VCM0(void, 0x28); }
    
    
    
    
    
    
    
    void u16() { VCM0(void, 0x48); }
    
    
    
    
    
    
    
    
    
    Unit3a3 * f70(s16 a0) { return VCM(Unit3a3 *, (void *, s16), 0x70, a0); }
};

typedef struct Sub64 {
    u8 pad0[0xC];
    VObj70 *obj;
} Sub64;

typedef struct Glob4C4 {
    u8 pad0[0x64];
    Sub64 *m64;
} Glob4C4;

typedef struct Sub20 {
    u8 pad0[0x24C];
    u8 m24C;
} Sub20;

typedef struct Glob4C0 {
    u8 pad0[0x18];
    void *m18;
    s32 m1C;
    Sub20 *m20;
} Glob4C0;

typedef struct T3710 {
    u8 pad0[0x10];
    s16 m10;
} T3710;

typedef struct Obj3a3 {
    u8 pad0[0x238];
    Desc3a3 *m238;
} Obj3a3;

extern "C" {
f32 RandFloat_13c010(void);
void PlayStatBumpChallengeStartedMaybe_3a1a30(Obj3a3 *, s32);
T3710 *CharaSysStateRuleLookupRelated_3a3710(Obj3a3 *);
void CharaStateReset_3a79b0(Desc3a3 *, s32, s32, s32, s32);
void ObjMgrPoolClear_3bb4b0(s32);
VObj37C * ObjSpawnTree_3bbe20(s32, long long, int, int);
void UnitSetSpawnParamRelated_3be020(VObj37C *, s32);
void PartyGetSavedLeaderPos_3caff0(void *, Vec3a3 *);
extern Glob4C0 *D_004837C0;
extern Glob4C4 *D_004837C4;
}

#pragma divbyzerocheck on

extern "C" s32 BattleSetupEncounter_3a3970(Obj3a3 *arg0, Desc3a3 *arg1, u8 arg2)
{
    Ent3a3 *src;
    s32 v;
    s32 sum;
    bool found;
    u8 b5;
    Ent3a3 *e;
    s32 k;
    Unit3a3 *u;
    Item3a3 *list;
    s32 i;
    bool any;
    s32 n;
    s32 cnt;
    T3710 *t;
    s32 m;
    Grp3a3 *grp;
    void *ptr;
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Vec3a3)) + (0x10)];
    Src18 *d;
    f32 range;
    s32 j;
    s32 a;
    Vec3a3 *pv;
    VObj37C *o;
    s16 id;
    s32 b;
    Ent3a3 *dst;

    if (arg1 == 0) {
        return 0;
    }
    if (D_004837C0 == 0 || D_004837C4 == 0) {
        return 0;
    }
    if (D_004837C0->m20->m24C & 1) {
        return 0;
    }
    ObjMgrPoolClear_3bb4b0(D_004837C0->m1C);
    k = 1;
    t = CharaSysStateRuleLookupRelated_3a3710(arg0);
    if (t != 0) {
        k = t->m10;
    }
    d = (arg0->m238 != 0) ? arg0->m238->m18 : 0;
    if (d != 0) {
        k = d->m10;
    }
    cnt = 0;
    for (i = 0; i < arg1->m44; i++) {
        id = arg1->ent[i].a;
        o = ObjSpawnTree_3bbe20(D_004837C0->m1C, (long long)(arg1->ent[i].b), 0, 0);
        if (o != 0) {
            UnitSetSpawnParamRelated_3be020(o, k);
            o->f37C(id);
            arg1->ent[i].obj = o;
            cnt++;
        }
    }
    b5 = 0;
    any = false;
    if (cnt > 0 && arg0->m238 != 0) {
        CharaStateReset_3a79b0(arg0->m238, 1, 0, 1, 1);
        sum = 0;
        src = arg1->ent;
        j = 0;
        arg0->m238->m8 = arg1->m8;
        arg0->m238->mA = arg1->mA;
        arg0->m238->mC = arg1->mC;
        arg0->m238->m10 = arg1->m10;
        arg0->m238->m14 = arg1->m14;
        arg0->m238->m18 = arg1->m18;
        arg0->m238->b0 = arg1->b0;
        arg0->m238->b1 = arg1->b1;
        arg0->m238->b2 = arg1->b2;
        arg0->m238->m2C = arg1->m2C;
        arg0->m238->m2E = arg1->m2E;
        arg0->m238->m30 = arg1->m30;
        arg0->m238->m40 = arg1->m40;
        arg0->m238->m44 = 0;
        dst = arg0->m238->ent;
        grp = &arg0->m238->grp;
        for (; j < arg1->m44; j++, src++) {
            b = src->b;
            a = src->a;
            ptr = src->obj;
            if (b < 0 || ptr == 0) {
                continue;
            }
            found = false;
            arg0->m238->m44++;
            dst->a = a;
            dst->b = b;
            dst->obj = ptr;
            dst++;
            for (m = 0; m < grp->n; m++) {
                Slot3a3 *s = &grp->e[m];
                if (s->p == 0) {
                    continue;
                }
                if (s->p->id != b) {
                    continue;
                }
                found = true;
                s->c++;
                break;
            }
            if (found) {
                continue;
            }
            if (grp->n >= 5) {
                continue;
            }
            u = D_004837C4->m64->obj->f70(b);
            if (u == 0) {
                continue;
            }
            {
                Slot3a3 *s = &grp->e[grp->n];
                s->p = u;
                s->c = 1;
            }
            grp->n++;
            sum += u->m2C;
            if (u->f5) {
                b5 = 1;
            }
            if (u->f6) {
                any = true;
            }
        }
        grp->avg = sum / grp->n;
        arg0->m238->m154 = 0;
        n = 0;
        list = 0;
        if (arg0->m238->m10 != 0) {
            n = arg0->m238->m10->n;
            list = arg0->m238->m10->list;
        }
        if (arg0->m238->m18 != 0) {
            Src18 *q = (*(Desc3a3 **)((u8 *)arg0 + 0x238))->m18;
            n = q->bits.n;
            list = q->list;
        }
        if (n > 0 && list != 0) {
            for (i = 0; i < n; i++, list++) {
                if ((s32)list->id < 0) {
                    continue;
                }
                if ((s32)list->pct <= 0) {
                    continue;
                }
                if ((s32)list->hi <= 0) {
                    continue;
                }
                if (!((s32)(100.0f * RandFloat_13c010()) < (s32)list->pct)) {
                    continue;
                }
                range = 1.0f + ((f32)list->hi - (f32)list->lo);
                v = list->lo + (s32)(range * RandFloat_13c010());
                if (v <= 0) {
                    continue;
                }
                m = arg0->m238->m154++;
                arg0->m238->rw[m].id = list->id;
                arg0->m238->rw[m].v = v;
            }
        }
        PartyGetSavedLeaderPos_3caff0(D_004837C0->m18, &(*(Vec3a3 *)(rgp_blk1 + 0x0)));
        arg0->m238->m34 = (*(Vec3a3 *)(rgp_blk1 + 0x0)).x;
        arg0->m238->m38 = (*(Vec3a3 *)(rgp_blk1 + 0x0)).y;
        arg0->m238->m3C = (*(Vec3a3 *)(rgp_blk1 + 0x0)).z;
        if (arg0->m238->m18 != 0) {
            pv = &arg0->m238->m18->v;
            if (pv->x != 0.0f || pv->y != 0.0f || pv->z != 0.0f) {
                arg0->m238->m34 = pv->x;
                arg0->m238->m38 = pv->y;
                arg0->m238->m3C = pv->z;
            }
        }
        arg0->m238->m162 = arg1->m162;
        arg0->m238->m164 = arg1->m164;
        arg0->m238->m166 = arg1->m166;
        arg0->m238->m178 = 0;
        arg0->m238->m180 = 0;
        arg0->m238->m188 = 0;
        arg0->m238->m168 = 0;
        arg0->m238->b3 = arg2;
        if (arg0->m238->m2C > 0) {
            if (arg0->m238->m30 <= 0.0f) {
                switch (arg0->m238->m2C) {
                case 0:
                    break;
                case 1:
                    arg0->m238->m30 = 60.0f * (9.0f * (f32)arg0->m238->m44);
                    if (any) {
                        if (arg0->m238->m2E == 2) {
                            arg0->m238->m2E = 0;
                        }
                    }
                    if (b5) {
                        arg0->m238->m2E = 0;
                    }
                    break;
                case 2:
                    arg0->m238->m30 = 60.0f * (6.0f * (f32)arg0->m238->m44);
                    break;
                case 3:
                    break;
                case 4:
                    arg0->m238->m30 = 60.0f * (5.0f * (f32)arg0->m238->m44);
                    break;
                case 5:
                    break;
                }
            }
            PlayStatBumpChallengeStartedMaybe_3a1a30(arg0, arg0->m238->m2C);
        }
    }
    return cnt;
}
