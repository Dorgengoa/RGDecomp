#include "types.h"

typedef struct Info {
    u8 pad0[4];
    s8 lo : 4;
    s8 hi : 4;
} Info;

class Chr {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void v0A4();
    virtual void v0A8();
    virtual void v0AC();
    virtual void v0B0();
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual void v0C0();
    virtual void v0C4();
    virtual void v0C8();
    virtual void v0CC();
    virtual void v0D0();
    virtual void v0D4();
    virtual void v0D8();
    virtual void v0DC();
    virtual void v0E0();
    virtual void v0E4();
    virtual void v0E8();
    virtual void v0EC();
    virtual void v0F0();
    virtual void v0F4();
    virtual void v0F8();
    virtual void v0FC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void v1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual void v1D4();
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual void v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void v280();
    virtual void v284();
    virtual void v288();
    virtual void v28C();
    virtual void v290();
    virtual void v294();
    virtual void v298();
    virtual void v29C();
    virtual void v2A0();
    virtual void v2A4();
    virtual void v2A8();
    virtual void v2AC();
    virtual void v2B0();
    virtual void v2B4();
    virtual void v2B8();
    virtual void v2BC();
    virtual void v2C0();
    virtual void v2C4();
    virtual void v2C8();
    virtual void v2CC();
    virtual void v2D0();
    virtual void v2D4();
    virtual void v2D8();
    virtual void v2DC();
    virtual void v2E0();
    virtual void v2E4();
    virtual void v2E8();
    virtual void v2EC();
    virtual void v2F0();
    virtual void v2F4();
    virtual void v2F8();
    virtual void v2FC();
    virtual void v300();
    virtual void v304();
    virtual void v308();
    virtual void v30C();
    virtual void v310();
    virtual void v314();
    virtual void v318();
    virtual void v31C();
    virtual void v320();
    virtual void v324();
    virtual void v328();
    virtual void v32C();
    virtual void v330();
    virtual void v334();
    virtual void v338();
    virtual void v33C();
    virtual void v340();
    virtual void v344();
    virtual void v348();
    virtual void v34C();
    virtual void v350();
    virtual Info *GetInfo();
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
            cur = TargetRefGetId_2e7120(CharaGetTargetRef_214a30(e));
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
