#include "types.h"

/* ONE symbol, TWO entry points: a virtual tail call (vtable slot 0x180,
   index 94) then the clamp/set accessor.  See src/s23c/ContainerViewGetAtFwd_40a290.cpp. */

typedef struct M {
    u8  pad000[0x1E];
    s16 m1E;
} M;

struct OD {
    u8 pad000[0x18];
    M *m18;
};

class O {
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
    virtual void v94(s32);
};

extern const s32 D_00465D68;

extern "C" void InsectItemAddDefense_3d1a40(O *o, s32 d)
{
    o->v94(((OD *)o)->m18->m1E + d);
}

extern "C" s16 func_003D1A40_e1(O *o, s32 v)
{
    OD *d = (OD *)o;

    if (v < 0) v = 0;
    /* ONE load of the limit: reading the extern twice made mwcc
       emit two lui/lw pairs, two words longer than retail. */
    {
        s32 lim = D_00465D68;
        if (v > lim) v = lim;
    }
    d->m18->m1E = (s16)v;
    return d->m18->m1E;
}
