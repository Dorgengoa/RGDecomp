#include "types.h"

struct B3D09C0 {
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
    virtual void v10();
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
    virtual s32 v26(s16 n);
};
struct C3D09C0 : B3D09C0 {};
struct M3D09C0 { u8 pad000[0x8]; struct C3D09C0 *f08; };
struct N3D09C0 { u8 pad000[0x40]; struct M3D09C0 *f40; };
struct G3D09C0 { u8 pad000[0x8]; struct N3D09C0 *f08; };
struct A3D09C0 { u8 pad000[0x4]; s16 f04; };
struct T3D09C0 { u8 pad000[0x18]; struct A3D09C0 *f18; };

extern "C" struct G3D09C0 *D_004838E8;

extern "C" s32 CageRecGetCatchDef_3d09c0(struct T3D09C0 *p)
{
    struct G3D09C0 *g;
    s32 n;

    g = D_004838E8;
    if (g == 0) return 0;
    n = p->f18->f04;
    if (n <= 0) return 0;
    return g->f08->f40->f08->v26(n);
}
