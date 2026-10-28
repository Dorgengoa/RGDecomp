/* rgp:protos */
#line 1
#include "types.h"

typedef struct Info {
    u8 pad0[4];
    s8 lo : 4;
    s8 hi : 4;
} Info;

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * GetInfo() { return VCM0(Info *, 0x354); }
};

typedef struct Ent { u8 pad0[0xA44]; s32 flags; } Ent;
typedef struct Party { u8 pad0[0x18E]; s16 mode; } Party;
typedef struct World { u8 pad0[0x18]; Party *party; void *chrs; } World;

extern "C" {
extern s32 GetCurrentScene_1f5be0(void);
extern void *GetActionMgr_1fdb50(void);
extern World *GetGameData_1fede0(void);
extern s32 ScriptGetInt_26a2a0(void *);
extern Ent *ActionMgrFindById_233b50(void *, s32);
extern void *CharaGetTargetRef_214a30(Ent *);
extern s32 TargetRefGetId_2e7120(void *);
extern Chr *ObjFindById_3bb3a0(void *, s32);
extern void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern s32 CharaGetAttachParentId_213890(Ent *);
extern void ScriptSetRefInt_26a1e0(void *, s32);
}

extern "C" s32 EvCmdSelectNthCharaMaybe_269290(u8 *self, s32 arg1)
{
    s32 hud;
    void *tbl;
    World *w;
    s32 want;
    s32 cnt;
    s32 sel;
    s32 cur;
    s32 i;
    s16 mode;
    Ent *e;
    Chr *c;
    Info *inf;

    if (arg1 < 2) {
        return 0;
    }
    hud = GetCurrentScene_1f5be0();
    tbl = GetActionMgr_1fdb50();
    w = GetGameData_1fede0();
    want = ScriptGetInt_26a2a0(self);
    sel = -1;
    cnt = 0;
    mode = w->party->mode;
    cur = sel;
    if (mode == 5) {
        e = ActionMgrFindById_233b50(tbl, mode);
        if (e != 0) {
            cur = ((short)TargetRefGetId_2e7120(CharaGetTargetRef_214a30(e)));
            e = ActionMgrFindById_233b50(tbl, cur);
            if (e != 0 && !(e->flags & 0x80000)) {
                c = ObjFindById_3bb3a0(w->chrs, cur);
                if (c != 0) {
                    inf = c->GetInfo();
                    if (inf != 0 && inf->hi != 0 && want == 0) {
                        sel = cur;
                    }
                }
            }
        }
    }
    if (sel < 0) {
        for (i = 0x80; i <= 0x9B; i++) {
            if (cur == i) {
                continue;
            }
            e = ActionMgrFindById_233b50(tbl, i);
            if (e == 0) {
                continue;
            }
            if (e->flags & 0x80000) {
                continue;
            }
            c = ObjFindById_3bb3a0(w->chrs, i);
            if (c == 0) {
                continue;
            }
            inf = c->GetInfo();
            if (inf == 0) {
                continue;
            }
            if (inf->hi == 0) {
                continue;
            }
            if (cnt != want) {
                cnt++;
                continue;
            }
            sel = i;
            break;
        }
    }
    if (sel >= 0) {
        ObjRecSetFlag2_1c3e80(hud, 1, sel);
        for (i = 0x80; i <= 0x9B; i++) {
            if (i == sel) {
                continue;
            }
            e = ActionMgrFindById_233b50(tbl, i);
            if (e == 0) {
                continue;
            }
            if (!(e->flags & 0x80000)) {
                continue;
            }
            if (sel != CharaGetAttachParentId_213890(e)) {
                continue;
            }
            ObjRecSetFlag2_1c3e80(hud, 1, i);
        }
    }
    ScriptSetRefInt_26a1e0(self + 8, sel);
    return 1;
}
