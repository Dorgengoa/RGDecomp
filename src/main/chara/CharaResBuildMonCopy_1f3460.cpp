#include "types.h"

/* jalr $25 == C++ virtual dispatch; slot = 8 + 4*index. */

class VE {
    u8 pad_[0x1B0];
public:
    virtual void vs0();
    virtual void vs1();
    virtual void vs2();
    virtual void vs3();
    virtual void vs4();
    virtual void vs5();
    virtual void vs6();
    virtual void vs7();
    virtual void vs8();
    virtual void vs9();
    virtual void vs10();
    virtual void vs11();
    virtual void vs12();
    virtual void vs13();
    virtual void vs14();
    virtual void f44(f32);
};

class VB {
public:
    virtual void vs0();
    virtual void vs1();
    virtual void vs2();
    virtual void vs3();
    virtual void vs4();
    virtual void vs5();
    virtual void vs6();
    virtual void vs7();
    virtual void vs8();
    virtual void vs9();
    virtual void vs10();
    virtual void vs11();
    virtual void vs12();
    virtual void vs13();
    virtual void vs14();
    virtual void vs15();
    virtual void vs16();
    virtual void vs17();
    virtual void vs18();
    virtual void vs19();
    virtual void vs20();
    virtual void vs21();
    virtual void vs22();
    virtual void vs23();
    virtual void vs24();
    virtual void vs25();
    virtual void vs26();
    virtual void vs27();
    virtual void vs28();
    virtual void vs29();
    virtual void vs30();
    virtual void vs31();
    virtual void vs32();
    virtual void vs33();
    virtual void vs34();
    virtual void vs35();
    virtual void vs36();
    virtual void vs37();
    virtual void vs38();
    virtual void vs39();
    virtual void vs40();
    virtual void vs41();
    virtual void vs42();
    virtual void vs43();
    virtual void vs44();
    virtual void vs45();
    virtual void vs46();
    virtual void vs47();
    virtual void vs48();
    virtual void vs49();
    virtual void vs50();
    virtual void vs51();
    virtual void vs52();
    virtual void vs53();
    virtual void vs54();
    virtual void vs55();
    virtual void vs56();
    virtual void vs57();
    virtual void vs58();
    virtual void vs59();
    virtual void vs60();
    virtual void vs61();
    virtual void vs62();
    virtual void vs63();
    virtual void vs64();
    virtual void vs65();
    virtual void vs66();
    virtual void vs67();
    virtual void vs68();
    virtual void vs69();
    virtual void vs70();
    virtual void vs71();
    virtual void vs72();
    virtual void vs73();
    virtual void vs74();
    virtual void vs75();
    virtual void vs76();
    virtual void vs77();
    virtual void vs78();
    virtual void vs79();
    virtual void vs80();
    virtual void vs81();
    virtual void vs82();
    virtual void vs83();
    virtual void vs84();
    virtual void vs85();
    virtual void vs86();
    virtual void vs87();
    virtual void vs88();
    virtual void vs89();
    virtual void vs90();
    virtual void vs91();
    virtual void vs92();
    virtual void vs93();
    virtual void vs94();
    virtual void vs95();
    virtual void vs96();
    virtual void vs97();
    virtual void vs98();
    virtual void vs99();
    virtual void vs100();
    virtual void vs101();
    virtual void vs102();
    virtual void vs103();
    virtual void vs104();
    virtual void vs105();
    virtual void vs106();
    virtual void vs107();
    virtual void vs108();
    virtual void vs109();
    virtual void vs110();
    virtual void vs111();
    virtual void vs112();
    virtual void vs113();
    virtual void vs114();
    virtual void vs115();
    virtual void vs116();
    virtual void vs117();
    virtual void vs118();
    virtual void vs119();
    virtual void vs120();
    virtual void vs121();
    virtual void vs122();
    virtual void vs123();
    virtual void vs124();
    virtual void vs125();
    virtual void vs126();
    virtual void vs127();
    virtual void vs128();
    virtual void vs129();
    virtual void vs130();
    virtual void vs131();
    virtual void vs132();
    virtual void vs133();
    virtual void vs134();
    virtual void vs135();
    virtual void vs136();
    virtual void vs137();
    virtual void vs138();
    virtual void vs139();
    virtual void vs140();
    virtual void vs141();
    virtual void vs142();
    virtual void vs143();
    virtual void vs144();
    virtual void vs145();
    virtual void vs146();
    virtual void vs147();
    virtual void vs148();
    virtual void vs149();
    virtual void vs150();
    virtual void vs151();
    virtual void vs152();
    virtual void vs153();
    virtual void vs154();
    virtual void vs155();
    virtual void vs156();
    virtual void vs157();
    virtual void vs158();
    virtual void vs159();
    virtual void vs160();
    virtual void vs161();
    virtual void vs162();
    virtual void vs163();
    virtual void vs164();
    virtual void vs165();
    virtual void vs166();
    virtual void vs167();
    virtual void vs168();
    virtual void vs169();
    virtual void vs170();
    virtual void vs171();
    virtual void vs172();
    virtual void vs173();
    virtual void vs174();
    virtual void vs175();
    virtual void vs176();
    virtual void vs177();
    virtual void vs178();
    virtual void vs179();
    virtual void vs180();
    virtual void vs181();
    virtual void vs182();
    virtual void vs183();
    virtual void vs184();
    virtual void vs185();
    virtual void vs186();
    virtual void vs187();
    virtual void vs188();
    virtual void vs189();
    virtual void vs190();
    virtual void vs191();
    virtual void vs192();
    virtual void vs193();
    virtual void vs194();
    virtual void vs195();
    virtual void vs196();
    virtual void vs197();
    virtual void vs198();
    virtual void vs199();
    virtual void vs200();
    virtual void vs201();
    virtual void vs202();
    virtual void vs203();
    virtual void vs204();
    virtual void vs205();
    virtual void vs206();
    virtual void vs207();
    virtual void vs208();
    virtual void vs209();
    virtual void vs210();
    virtual void vs211();
    virtual void vs212();
    virtual void vs213();
    virtual void vs214();
    virtual void vs215();
    virtual void vs216();
    virtual void vs217();
    virtual void vs218();
    virtual void vs219();
    virtual void vs220();
    virtual void vs221();
    virtual void vs222();
    virtual s32 f384();
};

struct St {
    s16 f0;
    s16 f2;
    s16 f4;
    u8  f6;
    u8  f7;
    u8  f8[4];
    char name[0x58];
    s16 f64;
};

struct P { u8 pad[0x6C]; s16 f6C; s16 f6E; s32 f70; };
struct Q { s32 f0; s32 f4; u8 pad8[0x20]; u8 f28; };
struct R { u8 pad[0x1C]; s32 f1C; };

extern "C" s32  GetCharaDataMgr_1fdb70(void);
extern "C" void GetCharaResMgr_1fdb60(void);
extern "C" s32  CharaDataGetLoadState_1ed5a0(s32, s16);
extern "C" P   *CharaDataFindById_1ed990(s32, s16);
extern "C" VE  *CharaDataGetNodeModel_1ed540(s32, s16, s32);
extern "C" s32  MemStackHeapAllocFront_14dd10(void *, s32);
extern "C" void MemStackClear_14dff0(char *);
extern "C" void MemStackInit_14d810(char *, s32, s32);
extern "C" u32  strlen(char *);
extern "C" char *strcpy(char *, char *);
extern "C" void GameSceneObjBindMaybe_1cfcd0(s32, s32, void *, s32);
extern "C" void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern "C" void ModelObjPlayMotionByName_1867a0(void *, char *, s32);
extern "C" Q   *ModelGetRootFrame_1511a0(void *);
extern "C" s32  ModelFindFrameIndexByName_151220(void *, char *);
extern "C" s32  ModelGetFrame_1511f0(void *, s32);
extern "C" void FrameSetDirty_14a5e0(Q *);
extern "C" s32  CharaDataGetKind4NodeDataMaybe_1ed460(s32, s16, s32, s32, s32);
extern "C" s32  MemStackAllocAligned64_14da10(char *, s32);
extern "C" s32  GetActionMgr_1fdb50(void);
extern "C" s32  ActionMgrFindById_233b50(s32, s32);
extern "C" s32  CharaGetAi_214a10(s32);
extern "C" void AiScriptLoad_2bbc50(s32, s32, s32, s32, s32);
extern "C" void AiResetState_2bbc30(s32);
extern "C" R   *GetGameData_1fede0(void);
extern "C" VB  *ObjFindById_3bb3a0(s32, s32);
extern "C" char D_0045B888[];
extern "C" char D_0045B890[];
extern "C" char D_0045B898[];

extern "C" void CharaResBuildMonCopy_1f3460(St *st, s32 ctx, void *heap)
{
    s32 h;
    VE *b;
    VE *c;
    s32 k;
    P *p;
    Q *q;
    VB *v;
    s32 r0;
    s32 r1;
    s32 r3;
    s32 r2;
    s32 t;

    h = GetCharaDataMgr_1fdb70();
    GetCharaResMgr_1fdb60();
    k = CharaDataGetLoadState_1ed5a0(h, st->f4);
    if (k == 2) {
        return;
    }
    if (k == 4) {
        st->f64 = 4;
        return;
    }
    b = 0;
    c = 0;
    p = CharaDataFindById_1ed990(h, st->f4);
    if (p != 0) {
        s32 ok = (p->f70 < 0) ^ 1;
        if (ok == 0) {
            b = CharaDataGetNodeModel_1ed540(h, st->f4, 0);
            if (b == 0) {
                st->f64 = 4;
                return;
            }
            p->f70 = st->f0;
            k = MemStackHeapAllocFront_14dd10(heap, 0x500);
            MemStackClear_14dff0(st->name);
            MemStackInit_14d810(st->name, k, 0x500);
            if (strlen(D_0045B888) <= 0xF) {
                strcpy(st->name, D_0045B888);
            }
            c = CharaDataGetNodeModel_1ed540(h, st->f4, 2);
            if (c == 0) {
                st->f64 = 4;
                return;
            }
        }
    }
    if (b != 0) {
        GameSceneObjBindMaybe_1cfcd0(ctx, st->f0, b, 0);
        ObjRecSetFlag2_1c3e80(ctx, 1, st->f0);
        ModelObjPlayMotionByName_1867a0(b, D_0045B890, 0);
        b->f44(0.0f);
        st->f6 = st->f6 | 1;
        GameSceneObjBindMaybe_1cfcd0(ctx, 0x9C, c, 0);
        ObjRecSetFlag2_1c3e80(ctx, 1, 0x9C);
        if (ModelGetRootFrame_1511a0(c) != 0) {
            t = ModelGetFrame_1511f0(b, ModelFindFrameIndexByName_151220(b, D_0045B898));
            q = ModelGetRootFrame_1511a0(c);
            q->f28 = 1;
            q->f4 = t;
            FrameSetDirty_14a5e0(q);
        }
        p = CharaDataFindById_1ed990(h, st->f4);
        if (p != 0) {
            p->f6C = p->f6C + 1;
        }
    }
    r0 = CharaDataGetKind4NodeDataMaybe_1ed460(h, st->f4, 0, 0, 0);
    r1 = MemStackAllocAligned64_14da10(st->name, 0x300);
    if (r0 != 0 && r1 == 0) {
        st->f64 = 4;
        return;
    }
    if (r0 != 0 && r1 != 0) {
        t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), st->f0);
        if (t != 0) {
            t = CharaGetAi_214a10(t);
            if (t != 0) {
                AiScriptLoad_2bbc50(t, r0, r1, 0x300, 0);
                AiResetState_2bbc30(t);
            }
            st->f6 = st->f6 | 8;
        }
    }
    v = ObjFindById_3bb3a0(GetGameData_1fede0()->f1C, st->f0);
    if (v != 0 && v->f384() != 0) {
        r2 = CharaDataGetKind4NodeDataMaybe_1ed460(h, st->f4, 1, 0, 0);
        r3 = MemStackAllocAligned64_14da10(st->name, 0x100);
        if (r2 != 0 && r3 == 0) {
            st->f64 = 4;
            return;
        }
        if (r2 != 0 && r3 != 0) {
            t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), st->f0);
            if (t != 0) {
                t = CharaGetAi_214a10(t);
                if (t != 0) {
                    AiScriptLoad_2bbc50(t, r2, r3, 0x100, 1);
                }
            }
        }
    }
    st->f6 = st->f6 | 0x80;
    st->f64 = 3;
}
