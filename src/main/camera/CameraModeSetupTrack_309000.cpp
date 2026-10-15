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
};

extern "C" void CameraChaseStep_161b60(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" void CameraModeSetupTrack_309000(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ((struct C192 *)p0)->v21();
    r1 = ((struct C192 *)p0)->v20();
    CameraChaseStep_161b60(p0, 1.0f);
}
