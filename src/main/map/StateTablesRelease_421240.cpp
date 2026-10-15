#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

extern "C" void StateTablesRelease_421240(struct Obj0 *p0)
{
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 t2;
    s32 rv3;
    s32 t3;
    s32 t4;
    s32 rv5;
    s32 t5;
    s32 t6;
    s32 rv7;
    s32 t7;
    s32 t8;
    s32 rv9;
    s32 t9;
    s32 t10;

    t0 = p0->m08;
    if (t0 != 0) {
        ((struct C0 *)t0)->v6();
        t1 = p0->m0C;
        rv1 = t1;
    } else {
        t2 = p0->m0C;
        rv1 = t2;
    }
    if (rv1 != 0) {
        ((struct C0 *)rv1)->v6();
        t3 = p0->m10;
        rv3 = t3;
    } else {
        t4 = p0->m10;
        rv3 = t4;
    }
    if (rv3 != 0) {
        ((struct C0 *)rv3)->v6();
        t5 = p0->m14;
        rv5 = t5;
    } else {
        t6 = p0->m14;
        rv5 = t6;
    }
    if (rv5 != 0) {
        ((struct C0 *)rv5)->v6();
        t7 = p0->m18;
        rv7 = t7;
    } else {
        t8 = p0->m18;
        rv7 = t8;
    }
    if (rv7 != 0) {
        ((struct C0 *)rv7)->v6();
        t9 = p0->m1C;
        rv9 = t9;
    } else {
        t10 = p0->m1C;
        rv9 = t10;
    }
    if (rv9 != 0) {
        ((struct C0 *)rv9)->v6();
        return;
    }
}
