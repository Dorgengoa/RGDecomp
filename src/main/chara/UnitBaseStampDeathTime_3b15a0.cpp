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
};

extern "C" s32 DoubleToUInt_13bb78(s64);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj1 * D_00483818;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x198];
    s32 m198;
};

struct Obj1 {
    u8 pad000[0x20];
    struct Obj2 *m20;
};

struct Obj2 {
    u8 pad000[0x238];
    struct Obj3 *m238;
};

struct Obj3 {
    u8 pad000[0x178];
    s64 m178;
};

extern "C" s32 UnitBaseStampDeathTime_3b15a0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 r0;
    s32 rv5;
    s32 t1;
    s32 rv4;
    struct Obj1 * t2;
    struct Obj2 * t3;
    struct Obj3 * t4;
    s32 rv3;
    s64 t5;
    s32 r2;

    t0 = D_00483818;
    if (t0 == 0) {
        return 0;
    }
    r0 = ((struct C0 *)p0)->v46();
    if (r0 == 0) {
        rv5 = 0;
    } else {
        t1 = p0->m198;
        rv4 = 1;
        if (t1 > 0) {
            rv4 = 0;
        } else {
            ((struct C0 *)p0)->v104(1, 1, 1);
            t4 = D_00483818->m20->m238;
            if (t4 != 0) {
                rv3 = DoubleToUInt_13bb78(t4->m178);
            } else {
                rv3 = 0;
            }
            p0->m198 = rv3;
            rv4 = 1;
        }
        rv5 = rv4;
    }
    return rv5;
}
