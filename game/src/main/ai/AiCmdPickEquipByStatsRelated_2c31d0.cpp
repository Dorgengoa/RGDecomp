#pragma divbyzerocheck on
#include "types.h"

class Obj2;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 isValid() { return VCM0(s32, 0x48); }
};

class Obj2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 val(s32 j, s32 f) { return VCM(s32, (void *, s32, s32), 0x178, j, f); }
};

class Mgr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Obj * get(s32 id) { return VCM(Obj *, (void *, s32), 0x2D0, id); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * cur() { return VCM0(void *, 0x470); }
};

typedef struct Ctx { u8 pad[0x14]; s32 m14; } Ctx;
typedef struct Data { u8 pad[0x18]; s8 v[5]; } Data;
typedef struct Tbl { u8 pad0[8]; s32 m8; u8 pad1[0x164 - 0xC]; s32 count; s32 ids[1]; } Tbl;

extern "C" {
extern Tbl D_004DB920;
void *GetGameData_1fede0(void);
Mgr *CharaMgrPoolFindById_3a8c60(s32 a, s32 b);
s32 ScriptSlotGetInt_2cc9c0(u64 *p);
void ScriptSlotStoreIntRef_2cc900(u64 *p, s32 v);
s32 EquipSlotGetRecId_3a0760(void *x);
Data *EquipSlotGetAbilityKind0Rec_3a0780(Obj *o);
Obj2 *ActorFindById_3eb870(Ctx *ctx, s32 id);
}

static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

extern "C" s32 AiCmdPickEquipByStatsRelated_2c31d0(u64 *p)
{
    s32 a[5] __attribute__((aligned(16)));
    s32 sum[5] __attribute__((aligned(16)));
    s32 tmp[5] __attribute__((aligned(16)));
    s32 id;
    s32 best;
    Ctx *ctx;
    s32 n;
    s32 k;
    s32 i;
    Obj *obj;
    Obj2 *o2;
    s32 j;
    s32 jj;
    Data *d;
    s32 second;
    Mgr *mgr;
    s8 *src;


    ctx = (Ctx *)GetGameData_1fede0();
    if ((mgr = CharaMgrPoolFindById_3a8c60(ctx->m14, D_004DB920.m8)) == 0) {
        return 0;
    }
    id = ScriptSlotGetInt_2cc9c0(p++);
    best = -1;
    second = -1;
    for (i = 0; i < 3; i++, id++) {
        obj = mgr->get(id);
        if (obj == 0) {
            continue;
        }
        if (obj->isValid() == 0) {
            break;
        }
        {
            void *c = mgr->cur();
            if (c != 0 && id == EquipSlotGetRecId_3a0760(c)) {
                break;
            }
        }
        d = EquipSlotGetAbilityKind0Rec_3a0780(obj);
        if (d == 0) {
            break;
        }
        src = d->v;
        for (j = 0; j < 5; j++) {
            s32 v;
            a[j] = v = src[j];
            if (v < 0 || v > 99) {
                a[j] = 0;
            }
        }
        clr(sum, sizeof(sum));
        n = 0;
        for (k = 0; k < D_004DB920.count; k++) {
            o2 = ActorFindById_3eb870(ctx, D_004DB920.ids[k]);
            if (o2 == 0) {
                continue;
            }
            for (jj = 0; jj < 5; jj++) {
                tmp[jj] = o2->val(jj, 1);
                sum[jj] += (a[jj] / 2 + 50) - (tmp[jj] + 100) / 2;
            }
            n++;
        }
        if (n == 0) {
            break;
        }
        for (j = 0; j < 5; j++) {
            sum[j] /= n;
        }
        for (j = 0; j < 5; j++) {
            if (a[j] != 0 && sum[j] >= 50) {
                second = id;
                break;
            }
        }
        if (j == 5) {
            best = id;
        }
    }
    ScriptSlotStoreIntRef_2cc900(p++, best);
    ScriptSlotStoreIntRef_2cc900(p, second);
    return 1;
}
