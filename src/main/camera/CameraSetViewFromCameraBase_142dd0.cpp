#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7(void *);
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
    virtual s32 v13(void *);
};

extern "C" void CameraSetView_156200(s32, void *, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xF20];
    s32 mF20;
};

extern "C" void CameraSetViewFromCameraBase_142dd0(struct Obj0 *p0, s32 p1)
{
    u128 v40[4];
    u128 v30;
    s32 t0;

    ((struct C192 *)p1)->v13(v40);
    ((struct C192 *)p1)->v7(&v30);
    t0 = p0->mF20;
    if (t0 != 0) {
        CameraSetView_156200(t0, v40, &v30);
        return;
    }
}
