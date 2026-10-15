#include "types.h"

/* MapAreaModelDrawBucket1_187030 -- 80 B, THREE entries, all virtual tail calls (vptr 0x68).
 *   e0 slot 0x30 (v10) with (0, 1);  e1 same with (0, 2);  e2 slot 0x84 (v31) */

struct VAB { unsigned char pad[0x68]; };
class VA : public VAB {
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
    virtual void v10(s32, s32);
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
};

extern "C" void MapAreaModelDrawBucket1_187030(VA *o) { o->v10(0, 1); }

extern "C" void func_00187030_e1(VA *o) { o->v10(0, 2); }

extern "C" void func_00187030_e2(VA *o) { o->v31(); }
