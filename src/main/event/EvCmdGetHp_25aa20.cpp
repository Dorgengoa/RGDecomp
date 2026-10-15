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
    virtual s32 v72(s32);
};


struct S8 { s32 a; s32 b; };

extern "C" s32 GetGameData_1fede0(void);
extern "C" s32 ScriptGetInt_26a2a0(struct S8 *);
extern "C" s32 ActorFindById_3eb870(s32, s32);
extern "C" void ScriptSetRefInt_26a1e0(struct S8 *, s32);

extern "C" s32 EvCmdGetHp_25aa20(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 rv6;
    s32 rv7;
    s32 r2;

    r0 = GetGameData_1fede0();
    r1 = ScriptGetInt_26a2a0(p0++);
    rv6 = 0;
    rv7 = 0;
    r2 = ActorFindById_3eb870(r0, r1);
    if (r2 != 0) {
        rv6 = ((struct C0 *)r2)->v58();
        rv7 = ((struct C0 *)r2)->v72(1);
    }
    ScriptSetRefInt_26a1e0(p0++, rv6);
    if (p1 == 3) {
        ScriptSetRefInt_26a1e0(p0, rv7);
    }
    return 1;
}
