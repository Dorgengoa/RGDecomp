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
    virtual s32 v68(s32);
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x96C];
    s32 m96C;
};

extern "C" s32 MenuObjInsectGetName_386d40(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m96C;
    if (t0 != 0) {
        ((struct C0 *)t0)->v68(0);
        return;
    }
    return 0;
}
