#include "types.h"

typedef struct Info { u8 pad[0x10]; s32 m10; } Info;

class Mgr {
public:
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual void p18();
    virtual void p19();
    virtual void p20();
    virtual void p21();
    virtual void p22();
    virtual void p23();
    virtual void p24();
    virtual void p25();
    virtual void p26();
    virtual void p27();
    virtual void p28();
    virtual void p29();
    virtual void p30();
    virtual void p31();
    virtual void p32();
    virtual void p33();
    virtual void p34();
    virtual void p35();
    virtual void p36();
    virtual void p37();
    virtual void p38();
    virtual void p39();
    virtual void p40();
    virtual void p41();
    virtual void p42();
    virtual void p43();
    virtual void p44();
    virtual void p45();
    virtual void p46();
    virtual void p47();
    virtual void p48();
    virtual void p49();
    virtual void p50();
    virtual void p51();
    virtual void p52();
    virtual void p53();
    virtual void p54();
    virtual void p55();
    virtual void p56();
    virtual void p57();
    virtual void p58();
    virtual void p59();
    virtual void p60();
    virtual void p61();
    virtual void p62();
    virtual void p63();
    virtual void p64();
    virtual void p65();
    virtual void p66();
    virtual void p67();
    virtual void p68();
    virtual void p69();
    virtual void p70();
    virtual void p71();
    virtual void p72();
    virtual void p73();
    virtual void p74();
    virtual void p75();
    virtual void p76();
    virtual void p77();
    virtual void p78();
    virtual void p79();
    virtual void p80();
    virtual void p81();
    virtual void p82();
    virtual void p83();
    virtual void p84();
    virtual void p85();
    virtual void p86();
    virtual void p87();
    virtual void p88();
    virtual void p89();
    virtual void p90();
    virtual void p91();
    virtual void p92();
    virtual void p93();
    virtual void p94();
    virtual void p95();
    virtual void p96();
    virtual void p97();
    virtual void p98();
    virtual void p99();
    virtual void p100();
    virtual void p101();
    virtual void p102();
    virtual void p103();
    virtual void p104();
    virtual void p105();
    virtual void p106();
    virtual void p107();
    virtual void p108();
    virtual void p109();
    virtual void p110();
    virtual void p111();
    virtual void p112();
    virtual void p113();
    virtual void p114();
    virtual void p115();
    virtual void p116();
    virtual void p117();
    virtual void p118();
    virtual void p119();
    virtual void p120();
    virtual void p121();
    virtual void p122();
    virtual void p123();
    virtual void p124();
    virtual void p125();
    virtual void p126();
    virtual void p127();
    virtual void p128();
    virtual void p129();
    virtual void p130();
    virtual void p131();
    virtual void p132();
    virtual void p133();
    virtual void p134();
    virtual void p135();
    virtual void p136();
    virtual void p137();
    virtual void p138();
    virtual void p139();
    virtual void p140();
    virtual void p141();
    virtual void p142();
    virtual void p143();
    virtual void p144();
    virtual void p145();
    virtual void p146();
    virtual void p147();
    virtual void p148();
    virtual void p149();
    virtual void p150();
    virtual void p151();
    virtual void p152();
    virtual void p153();
    virtual void p154();
    virtual void p155();
    virtual void p156();
    virtual void p157();
    virtual void p158();
    virtual void p159();
    virtual void p160();
    virtual void p161();
    virtual void p162();
    virtual void p163();
    virtual void p164();
    virtual void p165();
    virtual void p166();
    virtual void p167();
    virtual void p168();
    virtual void p169();
    virtual void p170();
    virtual void p171();
    virtual void p172();
    virtual void p173();
    virtual void p174();
    virtual void p175();
    virtual void p176();
    virtual void p177();
    virtual void p178();
    virtual void p179();
    virtual void p180();
    virtual void p181();
    virtual void p182();
    virtual void p183();
    virtual void p184();
    virtual void p185();
    virtual void p186();
    virtual void p187();
    virtual void p188();
    virtual void p189();
    virtual void p190();
    virtual void p191();
    virtual void p192();
    virtual void p193();
    virtual void p194();
    virtual void p195();
    virtual void p196();
    virtual void p197();
    virtual void p198();
    virtual void p199();
    virtual void p200();
    virtual void p201();
    virtual void p202();
    virtual void p203();
    virtual void p204();
    virtual void p205();
    virtual void p206();
    virtual void p207();
    virtual void p208();
    virtual void p209();
    virtual void p210();
    virtual void p211();
    virtual void p212();
    virtual void p213();
    virtual void p214();
    virtual void p215();
    virtual void p216();
    virtual void p217();
    virtual void p218();
    virtual void p219();
    virtual void p220();
    virtual void p221();
    virtual void p222();
    virtual Info *find(s32 k);
};

typedef struct Arg { s32 m0; s32 m4; s32 m8; s32 mC; s32 m10; s8 m14; } Arg;
typedef struct Ent { s32 m0; s32 m4; s32 m8; } Ent;
typedef struct Chr { u8 pad[0x4DC]; s32 m4DC; } Chr;
typedef struct Ctx { u8 pad[0x14]; s32 m14; } Ctx;

extern "C" {
extern char D_0045D6D8[];
void Sprintf_1343b8(char *buf, const char *fmt, s32 v);
Chr *ObjRecGetLiveObject_1c4a90(s32 a, s32 b);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
Ctx *GetGameData_1fede0(void);
s32 CharaGetActInfo_214cb0(s32 a);
s32 CharaGetActionTable_214cd0(s32 a);
s32 CharaActInfoGetTrail_2155b0(s32 a, s32 b);
void SwordTrailSetEndRef_2159b0(s32 a, s32 k, s32 id, s32 m8, s32 m4);
void SwordTrailSetup_215a10(s32 a, s32 b, void *c, f32 f0, f32 f1, f32 f2, f32 f3);
Ent *ActCfgTableFindVertByName_222cd0(s32 a, s32 b);
s32 ActionMgrFindById_233b50(s32 a, s32 b);
s32 GetEffectMgr_2d9040(void);
s32 EffectLookupTexByName_2e2d30(s32 a, s32 b, s32 c, s32 *d, void *e);
Mgr *CharaMgrPoolFindById_3a8c60(s32 a, s32 b);
s32 CharaPcResNameBuildMaybe_40dc60(s32 a);
}

extern "C" s32 CharaWeaponTrailSetup_22f500(Arg *a, s32 id, s32 x, f32 f0, f32 f1, f32 f2, f32 f3)
{
    s32 slot;
    char name[0x2C];
    u8 buf[0x20];
    s32 h;
    s32 lst;
    s32 obj;
    Ent *e0;
    Ent *e1;
    Chr *chr;

    h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (h == 0) {
        return 0;
    }
    lst = CharaGetActionTable_214cd0(h);
    if (lst == 0) {
        return 0;
    }
    obj = CharaActInfoGetTrail_2155b0(CharaGetActInfo_214cb0(h), x);
    if (obj == 0) {
        return 0;
    }
    switch (a->m14) {
    case 0:
    case 1:
    {
        s8 m;
        s32 k;
        s32 w = GetCurrentScene_1f5be0();
        m = a->m14;
        if (m == 0) {
            k = (id >= 0 && id < 12) ? id * 4 + 12 : -1;
        } else {
            k = (id >= 0 && id < 12) ? id * 4 + 14 : -1;
        }
        if (id == 1 && m == 1) {
            k = id;
        }
        if (id == 3 && m == 0) {
            k = id;
        }
        chr = ObjRecGetLiveObject_1c4a90(w, k);
    }
        if (chr == 0) {
            return 0;
        }
        {
            Mgr *mgr = CharaMgrPoolFindById_3a8c60(GetGameData_1fede0()->m14, id);
            Info *inf;
            s32 v;
            if (mgr == 0) {
                return 0;
            }
            inf = mgr->find(a->m14);
            if (inf == 0) {
                return 0;
            }
            v = inf->m10;
            if (v == 0) {
                return 0;
            }
            Sprintf_1343b8(name, D_0045D6D8, CharaPcResNameBuildMaybe_40dc60(v));
        }
        e0 = ActCfgTableFindVertByName_222cd0(lst, a->mC);
        if (e0 == 0) {
            return 0;
        }
        e1 = ActCfgTableFindVertByName_222cd0(lst, a->m10);
        if (e1 == 0) {
            return 0;
        }
        SwordTrailSetup_215a10(obj, chr->m4DC, name, f0, f1, f2, f3);
        SwordTrailSetEndRef_2159b0(obj, 0, id, e0->m8, e0->m4);
        SwordTrailSetEndRef_2159b0(obj, 1, id, e1->m8, e1->m4);
        return 1;
    }
    {
        s32 v = GetEffectMgr_2d9040();
        slot = -1;
        if (EffectLookupTexByName_2e2d30(v, a->m4, a->m8, &slot, buf) == 0) {
            return 0;
        }
    }
    if (0) {
        return 0;
    }
    e0 = ActCfgTableFindVertByName_222cd0(lst, a->mC);
    if (e0 == 0) {
        return 0;
    }
    e1 = ActCfgTableFindVertByName_222cd0(lst, a->m10);
    if (e1 == 0) {
        return 0;
    }
    SwordTrailSetup_215a10(obj, slot, buf, f0, f1, f2, f3);
    SwordTrailSetEndRef_2159b0(obj, 0, id, e0->m8, e0->m4);
    SwordTrailSetEndRef_2159b0(obj, 1, id, e1->m8, e1->m4);
    return 1;
}
