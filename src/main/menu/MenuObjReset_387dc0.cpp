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
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
};

extern "C" s32 memset(void *, s32, s32);
extern "C" void BitArray16Clear_384310(void *);
extern "C" void MenuObjParamsInit_387fd0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x784];
    s32 m784;
    u8 pad788[0x1D8];
    s32 m960;
    s32 m964;
    s32 m968;
    s32 m96C;
    s32 m970;
    u8 pad974[0x10];
    u8 m984;
    u8 m985;
    u8 pad986[0x2];
    s32 m988;
    u8 pad98C[0x38];
    s32 m9C4;
    s32 m9C8;
};

extern "C" void MenuObjReset_387dc0(struct Obj0 *p0)
{
    s32 r0;

    p0->m985 = 0;
    p0->m984 = 0;
    r0 = memset((struct Obj0 *)((u8 *)p0 + 0x974), 0, 0x10);
    p0->m96C = 0;
    p0->m970 = 0x7D0;
    p0->m968 = 0;
    p0->m964 = 0;
    p0->m960 = 0;
    p0->m9C4 = 0;
    p0->m9C8 = 0;
    BitArray16Clear_384310((struct Obj0 *)((u8 *)p0 + 0x986));
    p0->m988 = 0;
    MenuObjParamsInit_387fd0((struct Obj0 *)((u8 *)p0 + 0x990));
    ((struct C432 *)p0)->v21();
    ((struct C432 *)p0)->v18();
    p0->m784 = 0;
}
