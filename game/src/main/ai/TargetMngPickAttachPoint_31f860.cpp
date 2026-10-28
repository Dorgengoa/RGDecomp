#include "types.h"
#undef NULL
#define NULL 0

typedef struct Vec { f32 x, y, z, w; } Vec;

struct Obj {
    u8 pad0[0x90];
    Vec m90;
    u8 padA0[0x10];
    Vec mB0;
    u8 mC0[0x10];
};

struct Ctx {
    u8 pad0[0x1C];
    s32 m1C;
};

struct Chr {
    u8 pad0[0xA44];
    s32 mA44;
};

class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f22C() { return VCM0(s32, 0x22C); }
    u8 pad4[8];
    s32 mC;
};

extern "C" {
f32 VecDistance_13d3d0(Vec *, Vec *);
s32 ObjGetNthAttachPointPos_1ade20(s32, s32, s32, Vec *);
s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GetStaticScene_1c6c70();
s32 GetActionMgr_1fdb50();
s32 GetCharaResMgr_1fdb60();
Ctx *GetGameData_1fede0();
Chr *ActionMgrFindById_233b50(s32, s32);
s32 TargetRefResolve_2e5ed0(void *, s32);
void TargetRefSetAttachPoint_2e65f0(void *, s32, s32, s32);
Ent *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32 *, s32, s32);
f32 sceVu0InnerProduct(Vec *, Vec *);
void sceVu0Normalize(Vec *, Vec *);
void sceVu0SubVector(Vec *, Vec *, Vec *);
extern f32 D_0047D1EC;
extern f32 D_0047D248;
}

static inline bool isNull(Ent *e) { bool b; b = !(e != NULL); return b; }

extern "C" u8 TargetMngPickAttachPoint_31f860(Obj *arg0)
{
    s32 list[67] __attribute__((aligned(16)));
    s32 cur;
    Vec dir __attribute__((aligned(16)));
    Vec pos __attribute__((aligned(16)));
    s32 sys;
    s32 w;
    Ctx *c;
    s32 n;
    s32 prev;
    Ent *e;
    Chr *ch;
    f32 bestv;
    s32 best;
    s32 bestj;
    s32 i;
    s32 id;
    s32 h;
    s32 j;
    f32 d;
    f32 r;
    bool ok;

    sys = GetStaticScene_1c6c70();
    w = GetActionMgr_1fdb50();
    GetCharaResMgr_1fdb60();
    c = GetGameData_1fede0();
    n = 0;
    prev = -1;
    for (;;) {
        cur = -1;
        e = ObjMgrFindFiltered_3bb190(c->m1C, -1, 1, 0, prev, &cur, 0, 0);
        ok = e;
        if (!ok) {
            break;
        }
        if (cur < 0) {
            break;
        }
        ch = ActionMgrFindById_233b50(w, e->mC);
        if (e->f22C() != 0 && ch != NULL && !(ch->mA44 & 0x40)) {
            list[n++] = e->mC;
        }
        prev = cur + 1;
    }
    if (n <= 0) {
        return 0;
    }
    bestv = D_0047D1EC;
    best = -1;
    bestj = best;
    for (i = 0; i < n; i++) {
        id = list[i];
        if (ObjRecGetFlags_1c3d90(sys, 1, id) & 0x20000) {
            continue;
        }
        h = ObjRecGetLiveObject_1c4a90(sys, id);
        if (h == 0) {
            continue;
        }
        j = 0;
        while (ObjGetNthAttachPointPos_1ade20(h, 0x82, j, &pos) != 0) {
            j++;
            d = VecDistance_13d3d0(&pos, &arg0->m90);
            if (d < 0.0f) {
                continue;
            }
            sceVu0SubVector(&dir, &arg0->m90, &pos);
            sceVu0Normalize(&dir, &dir);
            r = sceVu0InnerProduct(&dir, &arg0->mB0);
            if (!(r <= D_0047D248)) {
                continue;
            }
            r = r / d;
            if (i == 0 || !(bestv <= r)) {
                bestv = r;
                best = id;
                bestj = j - 1;
            }
        }
    }
    if (best != -1) {
        TargetRefSetAttachPoint_2e65f0(arg0->mC0, best, 0x82, bestj);
        return TargetRefResolve_2e5ed0(arg0->mC0, 0);
    }
    return 0;
}
