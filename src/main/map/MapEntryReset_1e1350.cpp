#include "types.h"

struct C432 {
    u8 pad000[0x1B0];
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
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x790];
    s32 m790;
    s32 m794;
    s32 m798;
    s32 m79C;
};

extern "C" void MapEntryReset_1e1350(struct Obj0 *p0)
{
    p0->m790 = 0;
    ((struct C432 *)p0)->v18();
    p0->m794 = 0;
    p0->m798 = 0x3F800000;
    p0->m79C = -1;
}
