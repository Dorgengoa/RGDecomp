#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
    virtual s32 v13();
    virtual s32 v14();
    virtual s32 v15();
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
    virtual s32 v22();
    virtual s32 v23();
    virtual s32 v24();
    virtual s32 v25();
    virtual s32 v26();
    virtual s32 v27();
    virtual s32 v28();
    virtual s32 v29();
    virtual s32 v30();
    virtual s32 v31();
    virtual s32 v32();
    virtual s32 v33();
    virtual s32 v34();
    virtual s32 v35();
    virtual s32 v36();
    virtual s32 v37();
    virtual s32 v38();
    virtual s32 v39();
    virtual s32 v40();
    virtual s32 v41();
    virtual s32 v42();
    virtual s32 v43();
    virtual s32 v44();
    virtual s32 v45();
    virtual s32 v46();
    virtual s32 v47();
    virtual s32 v48();
    virtual s32 v49();
    virtual s32 v50();
    virtual s32 v51();
    virtual s32 v52();
    virtual s32 v53();
    virtual s32 v54();
    virtual s32 v55();
    virtual s32 v56();
    virtual s32 v57();
    virtual s32 v58();
    virtual s32 v59();
    virtual s32 v60();
    virtual s32 v61();
    virtual s32 v62();
    virtual s32 v63();
    virtual s32 v64();
    virtual s32 v65();
    virtual s32 v66();
    virtual s32 v67();
    virtual s32 v68();
    virtual s32 v69();
    virtual s32 v70();
    virtual s32 v71();
    virtual s32 v72();
    virtual s32 v73();
    virtual s32 v74();
    virtual s32 v75();
    virtual s32 v76();
    virtual s32 v77();
    virtual s32 v78();
    virtual s32 v79();
    virtual s32 v80();
    virtual s32 v81();
    virtual s32 v82();
    virtual s32 v83();
    virtual s32 v84();
    virtual s32 v85();
    virtual s32 v86();
    virtual s32 v87();
    virtual s32 v88();
    virtual s32 v89();
    virtual s32 v90();
    virtual s32 v91();
    virtual s32 v92();
    virtual s32 v93();
    virtual s32 v94();
    virtual s32 v95();
    virtual s32 v96();
    virtual s32 v97();
    virtual s32 v98();
    virtual s32 v99();
    virtual s32 v100();
    virtual s32 v101();
    virtual s32 v102();
    virtual s32 v103();
    virtual s32 v104(s32, s32, s32);
    virtual s32 v105();
    virtual s32 v106();
    virtual s32 v107();
    virtual s32 v108();
    virtual s32 v109();
    virtual s32 v110();
    virtual s32 v111();
    virtual s32 v112();
    virtual s32 v113();
    virtual s32 v114();
    virtual s32 v115();
    virtual s32 v116();
    virtual s32 v117();
    virtual s32 v118();
    virtual s32 v119();
    virtual s32 v120();
    virtual s32 v121();
    virtual s32 v122();
    virtual s32 v123();
    virtual s32 v124();
    virtual s32 v125();
    virtual s32 v126();
    virtual s32 v127();
    virtual s32 v128();
    virtual s32 v129();
    virtual s32 v130();
    virtual s32 v131();
    virtual s32 v132();
    virtual s32 v133();
    virtual s32 v134();
    virtual s32 v135();
    virtual s32 v136();
    virtual s32 v137();
    virtual s32 v138();
    virtual s32 v139();
    virtual s32 v140();
    virtual s32 v141();
    virtual s32 v142();
    virtual s32 v143();
    virtual s32 v144();
    virtual s32 v145();
    virtual s32 v146();
    virtual s32 v147();
    virtual s32 v148();
    virtual s32 v149();
    virtual s32 v150();
    virtual s32 v151();
    virtual s32 v152();
    virtual s32 v153();
    virtual s32 v154();
    virtual s32 v155();
    virtual s32 v156();
    virtual s32 v157();
    virtual s32 v158();
    virtual s32 v159();
    virtual s32 v160();
    virtual s32 v161();
    virtual s32 v162();
    virtual s32 v163();
    virtual s32 v164();
    virtual s32 v165();
    virtual s32 v166();
    virtual s32 v167();
    virtual s32 v168();
    virtual s32 v169();
    virtual s32 v170(s32, s32, s32);
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj0 * D_00483818;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x20];
    struct Obj1 *m20;
};

struct Obj1 {
    u8 pad000[0x24C];
    u8 m24C;
};

struct Obj2 {
    u8 pad000[0x408];
    u8 m408;
};

extern "C" s32 UnitOnBattleEnd_3bcec0(struct Obj2 *p0, s32 p1)
{
    struct Obj0 * t0;
    s32 r0;
    struct Obj0 * t1;
    struct Obj1 * t2;
    u8 t3;
    s32 rv3;
    u8 t4;
    s32 r1;
    s32 r2;

    t0 = D_00483818;
    if (t0 == 0) {
        return 0;
    }
    r0 = ((struct C0 *)p0)->v104(1, 1, 1);
    t1 = D_00483818;
    t2 = D_00483818->m20;
    t3 = D_00483818->m20->m24C;
    rv3 = 1;
    if ((t3 & 1) == 0) {
        rv3 = 0;
    } else {
        t4 = p0->m408;
        if ((((u64)(((s64)t4) << 0x38)) >> 0x3F) != 0) {
            r1 = ((struct C0 *)p0)->v170(0, 0, 1);
        }
        if (p1 == 3) {
            r2 = ((struct C0 *)p0)->v170(0, 0, 1);
        }
        rv3 = 1;
    }
    return rv3;
}
