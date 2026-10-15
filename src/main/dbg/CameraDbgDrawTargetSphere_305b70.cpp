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
    virtual s32 v40(void *);
};

extern "C" void * GetCurrentScene_1f5be0(void);
extern "C" s32 GetDrawCtx_15de80(void);
extern "C" s32 DrawListBeginPrim_141b00(s32);
extern "C" void GsPktSetTextured_13e400(s32, s32);
extern "C" void GsPktSetOriginMode_13e2f0(s32, s32);
extern "C" void GsPktSetAlphaBlend_13e500(s32, s32);
extern "C" void GsPktSetBlendMode_13e4f0(s32, s32);
extern "C" void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern "C" void GsPktSetZWriteMask_13e430(s32, s32);
extern "C" void GsPktEnableZTest_13e460(s32, s32);
extern "C" void DbgDrawSphere_1cc7e0(s32, void *, s32, f32);
extern "C" void DrawListEndPrim_141a20(s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4344];
    s32 m4344;
};

extern "C" void CameraDbgDrawTargetSphere_305b70(s32 p0, s32 p1, f32 fa0)
{
    u128 v50;
    struct Obj0 *r0;
    s32 t0;
    s32 r2;
    s32 r3;

    r0 = (struct Obj0 *)GetCurrentScene_1f5be0();
    t0 = r0->m4344;
    if (t0 == 0) {
        ((struct C192 *)p0)->v40(&v50);
        r2 = GetDrawCtx_15de80();
        r3 = DrawListBeginPrim_141b00(r2);
        GsPktSetTextured_13e400(r3, 0);
        GsPktSetOriginMode_13e2f0(r3, 1);
        GsPktSetAlphaBlend_13e500(r3, 1);
        GsPktSetBlendMode_13e4f0(r3, 1);
        GsPktEnableAlphaTest_13e4d0(r3, 1);
        GsPktSetZWriteMask_13e430(r3, 0);
        GsPktEnableZTest_13e460(r3, 1);
        DbgDrawSphere_1cc7e0(r3, &v50, p1, fa0);
        DrawListEndPrim_141a20(r2);
        return;
    }
}
