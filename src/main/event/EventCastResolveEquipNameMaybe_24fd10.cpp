#include "types.h"

struct Ent { u8 pad0[0x26]; s16 h26; s16 h28; s16 h2a; };
struct Sub { u8 pad0[0x10]; s16 *val; };
class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159();
    virtual void v160();
    virtual void v161();
    virtual void v162();
    virtual void v163();
    virtual void v164();
    virtual void v165();
    virtual void v166();
    virtual void v167();
    virtual void v168();
    virtual void v169();
    virtual void v170();
    virtual void v171();
    virtual void v172();
    virtual void v173();
    virtual void v174();
    virtual void v175();
    virtual void v176();
    virtual void v177();
    virtual void v178();
    virtual void v179();
    virtual void v180();
    virtual void v181();
    virtual void v182();
    virtual void v183();
    virtual void v184();
    virtual void v185();
    virtual void v186();
    virtual void v187();
    virtual void v188();
    virtual void v189();
    virtual void v190();
    virtual void v191();
    virtual void v192();
    virtual void v193();
    virtual void v194();
    virtual void v195();
    virtual void v196();
    virtual void v197();
    virtual void v198();
    virtual void v199();
    virtual void v200();
    virtual void v201();
    virtual void v202();
    virtual void v203();
    virtual void v204();
    virtual Ent *GetEnt();
    virtual void v206();
    virtual void v207();
    virtual void v208();
    virtual void v209();
    virtual void v210();
    virtual void v211();
    virtual void v212();
    virtual void v213();
    virtual void v214();
    virtual void v215();
    virtual void v216();
    virtual void v217();
    virtual void v218();
    virtual void v219();
    virtual void v220();
    virtual void v221();
    virtual void v222();
    virtual Sub *GetSub(s32);
    virtual void v224();
    virtual void v225();
    virtual void v226();
    virtual void v227();
    virtual void v228();
    virtual void v229();
    virtual void v230();
    virtual void v231();
    virtual void v232();
    virtual void v233();
    virtual void v234();
    virtual void v235();
    virtual void v236();
    virtual void v237();
    virtual void v238();
    virtual Sub *GetMain();
};
class Db {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void *Find(s16);
};
struct DbHolder { u8 pad0[8]; Db *db; };
struct Sys { u8 pad0[0x40]; DbHolder *h; };
struct Actor { u8 pad0[0x14]; s32 x14; s32 x18; };
struct Slot { u8 pad0[0xC]; s32 id; };
extern "C" {
s32 Sprintf_1343b8(char *, const char *, ...);
s32 Strstr_135138(const char *, const char *);
Actor *GetGameData_1fede0(void);
Sys *GetWorldDataMgr_1fedf0(void);
Obj *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Slot *PartyGetMemberChara_3c2420(s32, s32);
char *CharaPcResNameBuildMaybe_40dc60(void *);
}
extern char D_0045EA20[];
extern char D_0045EC78[];
extern char D_0045EC80[];
extern char D_0045EC90[];
extern char D_0045ECA0[];
extern char D_0045ECA8[];
extern char D_0045ECB0[];
extern char D_0045ECB8[];
extern char D_0045ECC0[];
extern char D_0045ECC8[];
extern char D_0045ECD0[];
extern char D_0045ECD8[];
extern char D_0045ECE0[];
extern char D_0045ECF0[];
extern char D_0045ED00[];
extern char D_0045ED10[];
extern char D_0045ED20[];

extern "C" s32 EventCastResolveEquipNameMaybe_24fd10(char *arg0, char *out, s32 *res, s32 *idx)
{
    bool ok;
    Actor *actor;
    s32 i;
    Sys *sys;
    Ent *e;
    s32 v;
    s32 kind;
    s32 n;
    s32 ret;
    Obj *o;
    Sub *p;
    void *r;

    if (*arg0 != 0x23) {
        return -1;
    }
    if (Strstr_135138(arg0, D_0045EC78) != 0) {
        kind = 0;
    } else if (Strstr_135138(arg0, D_0045EC80) != 0) {
        kind = 1;
    } else if (Strstr_135138(arg0, D_0045EC90) != 0) {
        kind = 2;
    } else {
        return -1;
    }
    if (Strstr_135138(arg0, D_0045ECA0) != 0) {
        *idx = 0;
    } else if (Strstr_135138(arg0, D_0045ECA8) != 0) {
        *idx = 1;
    } else if (Strstr_135138(arg0, D_0045ECB0) != 0) {
        *idx = 2;
    } else if (Strstr_135138(arg0, D_0045ECB8) != 0) {
        *idx = 3;
    } else if (Strstr_135138(arg0, D_0045ECC0) != 0) {
        *idx = 4;
    } else if (Strstr_135138(arg0, D_0045ECC8) != 0) {
        *idx = 5;
    } else if (Strstr_135138(arg0, D_0045ECD0) != 0) {
        *idx = 6;
    } else if (Strstr_135138(arg0, D_0045ECD8) != 0) {
        *idx = 7;
    } else if (Strstr_135138(arg0, D_0045ECE0) != 0) {
        *idx = 8;
    } else if (Strstr_135138(arg0, D_0045ECF0) != 0) {
        *idx = 9;
    } else if (Strstr_135138(arg0, D_0045ED00) != 0) {
        *idx = -1;
    } else if (Strstr_135138(arg0, D_0045ED10) != 0) {
        *idx = -2;
    } else {
        return -1;
    }
    actor = GetGameData_1fede0();
    sys = GetWorldDataMgr_1fedf0();
    if (*idx < 0) {
        n = PartyCountMembers_3c2010(actor->x18, 1, 1);
        for (i = 0; i < n; i++) {
            v = PartyGetMemberChara_3c2420(actor->x18, i)->id;
            if (v != 0) {
                if (*idx == -1) {
                    *idx = v;
                    break;
                }
                *idx = *idx + 1;
            }
        }
    }
    ret = -1;
    o = CharaMgrPoolFindById_3a8c60(actor->x14, *idx);
    if (o == 0) {
        return ret;
    }
    e = o->GetEnt();
    if (e == 0) {
        return ret;
    }
    switch (kind) {
    case 0:
        p = o->GetMain();
        if (p != 0) {
            ret = *p->val;
        } else {
            ret = e->h2a;
        }
        r = sys->h->db->Find(ret);
        if (r != 0) {
            Sprintf_1343b8(out, D_0045EA20, CharaPcResNameBuildMaybe_40dc60(r));
        } else {
            ret = -1;
        }
        *res = -1;
        break;
    case 1:
        p = o->GetSub(0);
        if (p != 0) {
            ret = *p->val;
        } else {
            ret = e->h26;
        }
        r = sys->h->db->Find(ret);
        if (r != 0) {
            Sprintf_1343b8(out, D_0045ED20, CharaPcResNameBuildMaybe_40dc60(r));
        } else {
            ret = -1;
        }
        ok = false;
        if (*idx >= 0 && *idx < 12) {
            ok = true;
        }
        *res = ok ? *idx * 4 + 0xC : -1;
        break;
    case 2:
        p = o->GetSub(1);
        if (p != 0) {
            ret = *p->val;
        } else {
            ret = e->h28;
        }
        r = sys->h->db->Find(ret);
        if (r != 0) {
            Sprintf_1343b8(out, D_0045ED20, CharaPcResNameBuildMaybe_40dc60(r));
        } else {
            ret = -1;
        }
        ok = false;
        if (*idx >= 0 && *idx < 12) {
            ok = true;
        }
        *res = ok ? *idx * 4 + 0xE : -1;
        break;
    }
    return ret;
}
