#include "types.h"

class C0 {
public:
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
    virtual s32 v104();
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
    virtual void v148(s32 a, s32 b);
};

struct Root {
    u8 pad00[0x1C];
    void *m1C;
};

extern void *D_004DB928 __attribute__((section(".data")));
struct Slot {
    s32 a;
    s32 b;
};

extern "C" void *ScriptSlotGetInt_2cc9c0(struct Slot *a);
extern "C" struct Root *GetGameData_1fede0(void);
extern "C" class C0 *ObjFindById_3bb3a0(void *a, void *b);

extern "C" s32 AiCmdObjSetStatusFxB_2c1c20(void *a0, s32 mode)
{
    void *x;
    void *y;
    class C0 *o;
    struct Slot *p;

    p = (struct Slot *)a0;
    x = D_004DB928;
    if (mode == 2) {
        x = ScriptSlotGetInt_2cc9c0(p++);
    }
    y = ScriptSlotGetInt_2cc9c0(p);
    o = ObjFindById_3bb3a0(GetGameData_1fede0()->m1C, x);
    if (o != 0) {
        o->v148(y != 0, 0);
    }
    return 1;
}
