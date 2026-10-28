#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  Slot byte offset = 8 + 4*index,
   because mwcc's vtable carries two leading words. */

struct Info { u8 pad00[0x2]; s16 f2; };
struct CObj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * v53() { return VCM0(Info *, 0xDC); }
};

struct Sub { u8 pad00[0x24]; s16 f24; };
struct Ent { u8 pad00[0xC]; Sub *fC; };

struct Self {
    u8  pad000[0xA8];
    s16 fA8;
    u8  padAA[0x2];
    s16 fAC;
    u8  padAE[0xC4];
    s16 f172;
    s16 f174;
};

extern "C" void *GetActionMgr_1fdb50(void);
extern "C" void *ActionMgrFindById_233b50(void *, s32);
extern "C" s32 CharaIsGroundReadyMaybe_210850(void *);
extern "C" Ent *GetGameData_1fede0(void);
extern "C" void *ActorFindById_3eb870(Ent *, s32);
extern "C" s32 Rand_133710(void);

extern "C" void AiRollActionChanceMaybe_2bb630(Self *p, s32 unused, s32 a, s32 b)
{
    void *o;
    Ent *e;
    void *ob;
    Info *r;
    s32 v;

    if (p->f174 > 0) {
        return;
    }
    o = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), p->fA8);
    if (o == 0) {
        return;
    }
    if (CharaIsGroundReadyMaybe_210850(o) == 0) {
        return;
    }
    e = GetGameData_1fede0();
    ob = ActorFindById_3eb870(e, p->fA8);
    if (ob == 0) {
        return;
    }
    r = ((CObj *)ob)->v53();
    if (r == 0) {
        return;
    }
    v = r->f2;
    if (e->fC->f24 == 3) {
        v = (s16)(v * 2);
    }
    if (Rand_133710() % 0x32 < (s16)v) {
        p->f172 = a;
        p->f174 = b;
        if ((s16)b <= 0) {
            p->fAC = 0x258;
        }
    }
}
