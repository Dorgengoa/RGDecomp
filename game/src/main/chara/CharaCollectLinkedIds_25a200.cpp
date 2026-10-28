/* PARKED at the RIGHT LENGTH (94/94 words), 15 bad -- every one of them
   is the same swap: retail has n=$18 and o=$17, this file has n=$17 and
   o=$18.  PREDICTED FIX (not yet built): declare `s32 n;` BEFORE `Obj *o;`
   (callee-saved regs descend in declaration order).  Out of round trips. */
#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  Slot byte offset = 8 + 4*index,
   because mwcc's vtable carries two leading words. */

struct Lst { u8 pad00[0x18]; s16 f18; void **f1C; };
struct CMgr {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Lst * v26(s32 a0) { return VCM(Lst *, (void *, s32), 0x70, a0); }
};

struct Rec { u8 pad00[0x2]; s16 f2; };
struct Sys { u8 pad00[0xC]; void *fC; };
struct World { u8 pad00[0x64]; Sys *f64; };
struct Reg { u8 pad00[0x1C]; void *f1C; };
struct Hit { u8 pad00[0xC]; s32 fC; };
struct Obj { u8 pad000[0xA44]; s32 fA44; };

extern "C" void GetCurrentScene_1f5be0(void);
extern "C" Reg *GetGameData_1fede0(void);
extern "C" World *GetWorldDataMgr_1fedf0(void);
extern "C" void *GetCharaResMgr_1fdb60(void);
extern "C" void *GetActionMgr_1fdb50(void);
extern "C" Obj *ActionMgrFindById_233b50(void *, s32);
extern "C" s32 CharaGetAttachParentId_213890(Obj *);
extern "C" Rec *CharaResFindById_1f0530(void *, s32);
extern "C" Hit *ObjMgrFindFiltered_3bb190(void *, s32, s32, s32, s32, s32, s32, s32);

extern "C" s32 CharaCollectLinkedIds_25a200(s32 key, s32 *out)
{
    Reg *g;
    World *w;
    void *sc;
    s32 n;
    Obj *o;
    Rec *r;
    void *mgr;
    Lst *lst;
    s32 i;
    void *e;
    Hit *h;

    GetCurrentScene_1f5be0();
    g = GetGameData_1fede0();
    w = GetWorldDataMgr_1fedf0();
    sc = GetCharaResMgr_1fdb60();
    n = 0;
    o = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), key);
    /* every guard here FALLS THROUGH into the continuation and every exit
       reaches one shared `return n`, so these are nested ifs, not early
       returns: an early return costs an extra `b` at each guard. */
    if (o != 0) {
        if ((o->fA44 & 0x80000) != 0) {
            if (CharaGetAttachParentId_213890(o) >= 0) {
                key = CharaGetAttachParentId_213890(o);
            }
        }
        out[n] = key;
        n++;
        r = CharaResFindById_1f0530(sc, key);
        if (r != 0) {
            mgr = w->f64->fC;
            lst = ((CMgr *)mgr)->v26(r->f2);
            if (lst != 0) {
                for (i = 0; i < lst->f18; i++) {
                    e = lst->f1C[i];
                    if (e == 0) {
                        continue;
                    }
                    h = ObjMgrFindFiltered_3bb190(g->f1C, *(s16 *)e, 1, 1, 0, 0, 0, 0);
                    if (h != 0) {
                        out[n] = h->fC;
                        n++;
                    }
                }
            }
        }
    }
    return n;
}
