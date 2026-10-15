#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  Slot byte offset = 8 + 4*index,
   because mwcc's vtable carries two leading words. */

struct Rec { u8 pad00[0x4]; void *f4; };
struct CObj {
    virtual Rec *v0();
    virtual Rec *v1();
    virtual Rec *v2();
    virtual Rec *v3();
    virtual Rec *v4();
    virtual Rec *v5();
    virtual Rec *v6();
    virtual Rec *v7();
    virtual Rec *v8();
    virtual Rec *v9();
    virtual Rec *v10();
    virtual Rec *v11();
    virtual Rec *v12();
    virtual Rec *v13();
    virtual Rec *v14();
    virtual Rec *v15();
    virtual Rec *v16();
    virtual Rec *v17();
    virtual Rec *v18();
    virtual Rec *v19();
    virtual Rec *v20();
    virtual Rec *v21();
    virtual Rec *v22();
    virtual Rec *v23();
    virtual Rec *v24();
    virtual Rec *v25();
    virtual Rec *v26();
    virtual Rec *v27();
    virtual Rec *v28();
    virtual Rec *v29();
    virtual Rec *v30();
    virtual Rec *v31();
    virtual Rec *v32();
    virtual Rec *v33();
    virtual Rec *v34();
    virtual Rec *v35();
    virtual Rec *v36();
    virtual Rec *v37();
    virtual Rec *v38();
    virtual Rec *v39();
    virtual Rec *v40();
    virtual Rec *v41();
    virtual Rec *v42();
    virtual Rec *v43();
    virtual Rec *v44();
    virtual Rec *v45();
    virtual Rec *v46();
    virtual Rec *v47();
    virtual Rec *v48();
    virtual Rec *v49();
    virtual Rec *v50();
    virtual Rec *v51();
    virtual Rec *v52();
    virtual Rec *v53();
    virtual Rec *v54();
    virtual Rec *v55();
    virtual Rec *v56();
    virtual Rec *v57();
    virtual Rec *v58();
    virtual Rec *v59();
    virtual Rec *v60();
    virtual Rec *v61();
    virtual Rec *v62();
    virtual Rec *v63();
    virtual Rec *v64();
    virtual Rec *v65();
    virtual Rec *v66();
    virtual Rec *v67();
    virtual Rec *v68();
    virtual Rec *v69();
    virtual Rec *v70();
    virtual Rec *v71();
    virtual Rec *v72();
    virtual Rec *v73();
    virtual Rec *v74();
    virtual Rec *v75();
    virtual Rec *v76();
    virtual Rec *v77();
    virtual Rec *v78();
    virtual Rec *v79();
    virtual Rec *v80();
    virtual Rec *v81();
    virtual Rec *v82();
    virtual Rec *v83();
    virtual Rec *v84();
    virtual Rec *v85();
    virtual Rec *v86();
    virtual Rec *v87();
    virtual Rec *v88();
    virtual Rec *v89();
    virtual Rec *v90();
    virtual Rec *v91();
    virtual Rec *v92();
    virtual Rec *v93();
    virtual Rec *v94();
    virtual Rec *v95();
    virtual Rec *v96();
    virtual Rec *v97();
    virtual Rec *v98();
    virtual Rec *v99();
    virtual Rec *v100();
    virtual Rec *v101();
    virtual Rec *v102();
    virtual Rec *v103();
    virtual Rec *v104();
    virtual Rec *v105();
    virtual Rec *v106();
    virtual Rec *v107();
    virtual Rec *v108();
    virtual Rec *v109();
    virtual Rec *v110();
    virtual Rec *v111();
    virtual Rec *v112();
    virtual Rec *v113();
    virtual Rec *v114();
    virtual Rec *v115();
    virtual Rec *v116();
    virtual Rec *v117();
    virtual Rec *v118();
    virtual Rec *v119();
    virtual Rec *v120();
    virtual Rec *v121();
    virtual Rec *v122();
    virtual Rec *v123();
    virtual Rec *v124();
    virtual Rec *v125();
    virtual Rec *v126();
    virtual Rec *v127();
    virtual Rec *v128();
    virtual Rec *v129();
    virtual Rec *v130();
    virtual Rec *v131();
    virtual Rec *v132();
    virtual Rec *v133();
    virtual Rec *v134();
    virtual Rec *v135();
    virtual Rec *v136();
    virtual Rec *v137();
    virtual Rec *v138();
    virtual Rec *v139();
    virtual Rec *v140();
    virtual Rec *v141();
    virtual Rec *v142();
    virtual Rec *v143();
    virtual Rec *v144();
    virtual Rec *v145();
    virtual Rec *v146();
    virtual Rec *v147();
    virtual Rec *v148();
    virtual Rec *v149();
    virtual Rec *v150();
    virtual Rec *v151();
    virtual Rec *v152();
    virtual Rec *v153();
    virtual Rec *v154();
    virtual Rec *v155();
    virtual Rec *v156();
    virtual Rec *v157();
    virtual Rec *v158();
    virtual Rec *v159();
    virtual Rec *v160();
    virtual Rec *v161();
    virtual Rec *v162();
    virtual Rec *v163();
    virtual Rec *v164();
    virtual Rec *v165();
    virtual Rec *v166();
    virtual Rec *v167();
    virtual Rec *v168();
    virtual Rec *v169();
    virtual Rec *v170();
    virtual Rec *v171();
    virtual Rec *v172();
    virtual Rec *v173();
    virtual Rec *v174();
    virtual Rec *v175();
    virtual Rec *v176();
    virtual Rec *v177();
    virtual Rec *v178();
    virtual Rec *v179();
    virtual Rec *v180();
    virtual Rec *v181();
    virtual Rec *v182();
    virtual Rec *v183();
    virtual Rec *v184();
    virtual Rec *v185();
    virtual Rec *v186();
    virtual Rec *v187();
    virtual Rec *v188();
    virtual Rec *v189();
    virtual Rec *v190();
    virtual Rec *v191();
    virtual Rec *v192();
    virtual Rec *v193();
    virtual Rec *v194();
    virtual Rec *v195();
    virtual Rec *v196();
    virtual Rec *v197();
    virtual Rec *v198();
    virtual Rec *v199();
    virtual Rec *v200();
    virtual Rec *v201();
    virtual Rec *v202();
    virtual Rec *v203();
    virtual Rec *v204();
    virtual Rec *v205();
};

struct Hit2 { u8 pad00[0xC]; void *fC; };
struct Hit { u8 pad00[0x10]; Hit2 *f10; };
struct Reg { u8 pad00[0x14]; void *f14; void *f18; u8 pad1C[0x4]; void *f20; };
struct Sys { u8 pad000[0x244]; void *f244; };
struct Reg2 { u8 pad00[0x20]; Sys *f20; };

extern s32 D_004825DC;
extern "C" Reg *GetGameData_1fede0(void);
extern "C" Hit *InvFindInCategoryRange_3c8370(void *, void *, s32, s32, s32, s32);
extern "C" char *ScriptStrTableNextScratch_2ccde0(s32 *);
extern "C" void *CharaMgrPoolFindById_3a8c60(void *, void *);
extern "C" char *MsgGetTextByIndex_279040(s32);
extern "C" void Sprintf_1343b8(char *, char *, void *, void *);
extern "C" u32 strlen(char *);
extern "C" void CharaSysEventLogKeyAdd_3a33b0(void *, s32, s32);
extern "C" void CharaEventLogRecord_3a62f0(void *, s32, s32, s32, s32);
extern "C" void CharaSysEventLogKeyRemove_3a3380(void *, s32);
extern "C" void FieldHudLogOpen_203fb0(void);

extern "C" void CharaEventLogAddItemUse_2ccc40(void *a, void *b)
{
    s32 out;
    char *buf;
    Reg *e;
    Hit *r;
    void *u;
    Rec *w;
    Hit2 *r2;
    void *z;

    if (D_004825DC == 0) {
        return;
    }
    e = GetGameData_1fede0();
    r = InvFindInCategoryRange_3c8370(e->f18, b, 0, -1, 0, 0);
    if (r == 0) {
        return;
    }
    buf = ScriptStrTableNextScratch_2ccde0(&out);
    u = CharaMgrPoolFindById_3a8c60(e->f14, a);
    if (buf == 0) {
        return;
    }
    if (u == 0) {
        return;
    }
    w = ((CObj *)u)->v205();
    r2 = r->f10;
    if (r2 == 0) {
        return;
    }
    if (w == 0) {
        return;
    }
    Sprintf_1343b8(buf, MsgGetTextByIndex_279040(0x26), w->f4, r2->fC);
    if (strlen(buf) < 0x50) {
        z = ((Reg2 *)GetGameData_1fede0())->f20->f244;
        if (z == 0) {
            return;
        }
        CharaSysEventLogKeyAdd_3a33b0(e->f20, out, 0);
        CharaEventLogRecord_3a62f0(z, out, out, -2, 1);
        CharaSysEventLogKeyRemove_3a3380(e->f20, out);
        FieldHudLogOpen_203fb0();
    }
}
