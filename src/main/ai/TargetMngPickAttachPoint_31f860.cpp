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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual s32 f22C();
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
    s32 list[67];
    s32 cur;
    Vec dir;
    Vec pos;
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
