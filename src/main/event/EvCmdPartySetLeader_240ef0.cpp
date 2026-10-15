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
    virtual s32 v59(s32);
};

extern "C" void * GetGameData_1fede0(void);
extern "C" s32 ScriptGetInt_2490f0(s32);
extern "C" s32 PartySetLeader_3c1600(s32, s32, s32);
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    s32 m18;
};

extern "C" s32 EvCmdPartySetLeader_240ef0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 r1;
    s32 t0;
    s32 r2;
    s32 t1;
    s32 r3;
    s32 rv7;
    s32 r4;

    if (p1 != 1) {
        return 0;
    }
    r0 = (struct Obj0 *)GetGameData_1fede0();
    r1 = ScriptGetInt_2490f0(p0);
    t0 = r0->m18;
    r2 = PartySetLeader_3c1600(t0, r1, 0);
    t1 = r0->m14;
    r3 = CharaMgrPoolFindById_3a8c60(t1, r1);
    rv7 = 1;
    if (r3 == 0) {
        rv7 = 0;
    } else {
        r4 = ((struct C0 *)r3)->v46();
        if (r4 != 0) {
            ((struct C0 *)r3)->v59(1);
            ((struct C0 *)r3)->v13();
        }
        rv7 = 1;
    }
    return rv7;
}
