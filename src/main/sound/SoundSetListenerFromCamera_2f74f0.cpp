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
    virtual s32 v39(void *);
    virtual s32 v40(void *);
};

extern "C" void * GetCurrentScene_1f5be0(void);
extern "C" s32 ObjRecGetLiveObject_1c3bc0(void *, s32);
extern "C" void VecSub_13be40(void *, void *, void *);
extern "C" void SoundSetListener_1b7fa0(void *, void *);
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

extern "C" void SoundSetListenerFromCamera_2f74f0(void)
{
    u128 v30;
    u128 v20;
    struct Obj0 *r0;
    s32 t0;
    s32 r1;

    r0 = (struct Obj0 *)GetCurrentScene_1f5be0();
    t0 = r0->m4344;
    r1 = ObjRecGetLiveObject_1c3bc0(r0, t0);
    ((struct C192 *)r1)->v39(&v30);
    ((struct C192 *)r1)->v40(&v20);
    VecSub_13be40(&v20, &v20, &v30);
    SoundSetListener_1b7fa0(&v30, &v20);
}
