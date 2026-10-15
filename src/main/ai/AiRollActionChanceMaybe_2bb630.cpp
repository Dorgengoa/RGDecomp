#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  Slot byte offset = 8 + 4*index,
   because mwcc's vtable carries two leading words. */

struct Info { u8 pad00[0x2]; s16 f2; };
struct CObj {
    virtual Info *v0();
    virtual Info *v1();
    virtual Info *v2();
    virtual Info *v3();
    virtual Info *v4();
    virtual Info *v5();
    virtual Info *v6();
    virtual Info *v7();
    virtual Info *v8();
    virtual Info *v9();
    virtual Info *v10();
    virtual Info *v11();
    virtual Info *v12();
    virtual Info *v13();
    virtual Info *v14();
    virtual Info *v15();
    virtual Info *v16();
    virtual Info *v17();
    virtual Info *v18();
    virtual Info *v19();
    virtual Info *v20();
    virtual Info *v21();
    virtual Info *v22();
    virtual Info *v23();
    virtual Info *v24();
    virtual Info *v25();
    virtual Info *v26();
    virtual Info *v27();
    virtual Info *v28();
    virtual Info *v29();
    virtual Info *v30();
    virtual Info *v31();
    virtual Info *v32();
    virtual Info *v33();
    virtual Info *v34();
    virtual Info *v35();
    virtual Info *v36();
    virtual Info *v37();
    virtual Info *v38();
    virtual Info *v39();
    virtual Info *v40();
    virtual Info *v41();
    virtual Info *v42();
    virtual Info *v43();
    virtual Info *v44();
    virtual Info *v45();
    virtual Info *v46();
    virtual Info *v47();
    virtual Info *v48();
    virtual Info *v49();
    virtual Info *v50();
    virtual Info *v51();
    virtual Info *v52();
    virtual Info *v53();
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
